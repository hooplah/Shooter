#include "ShooterServer.h"

#include <map>

#include "Assets.h"
#include "Context.h"
#include "PacketId.h"
#include "ServerPlayer.h"
#include "WorldServer.h"

ShooterServer::ShooterServer() : mSocket("0.0.0.0", 30000),
    mRunPacketThread(true),
    mPacketListener(listenForPackets, &mSocket, &mPacketMutex, &mPacketQueue, &mRunPacketThread, &mClientMutex, &mClients)
{
}

ShooterServer::~ShooterServer()
{
    mPacketMutex.lock();
    mRunPacketThread = false;
    mPacketMutex.unlock();
    mPacketListener.join();
}

void ShooterServer::update(Context& context, WorldServer& world)
{
    mPacketMutex.lock();
    while (!mPacketQueue.empty())
    {
        std::tuple<ClientId, Packet> packet_tuple = mPacketQueue.front();
        mPacketQueue.pop();
        auto& client = std::get<0>(packet_tuple);
        auto& packet = std::get<1>(packet_tuple);

        ClientPacketId packetId;
        packet >> packetId;

        switch (packetId)
        {
            case ClientPacketId::CONNECT:
            {
                std::cout << "Client connected\n";
                Packet outPacket;
                outPacket << ServerPacketId::ACCEPT_CONNECT;
                send(outPacket, client);

                Packet playerPacket;
                playerPacket << ServerPacketId::SPAWN_YOU;
                auto player = createServerPlayer(context, Assets::sprites["ammocrate"], sf::Vector2f(0.f, 0.f));
                player->serialize(context, playerPacket);
                send(playerPacket, client);

                world.addGameObject(std::move(player));

                break;
            }
        }
    }
    mPacketMutex.unlock();
}

void ShooterServer::send(const Packet& packet, ClientId& client)
{
    mClientMutex.lock();
    ClientHandle& clientHandle = mClients[client];
    mSocket.sendTo(packet.getData(), packet.getDataSize(), clientHandle.mAddress, clientHandle.mPort);
    mClientMutex.unlock();
}

void ShooterServer::listenForPackets(UDPSocket* socket, std::mutex* packetMutex,
                                     std::queue<std::tuple<ClientId, Packet>>* packetQueue,
                                     bool* runPacketThread,
                                     std::mutex* clientMutex, std::map<ClientId, ClientHandle>* clients)
{
    unsigned char buffer[1024];
    ClientHandle client;
    std::map<ClientHandle, ClientId> clientMap;
    ClientId nextClient = 0;

    while (true)
    {
        int packetSize = socket->recvFrom(buffer, 1024, client.mAddress, client.mPort);
        Packet packet(buffer, packetSize);

        packetMutex->lock();

        if (!*runPacketThread)
        {
            packetMutex->unlock();
            break;
        }

        auto clientIterator = clientMap.find(client);
        ClientId clientId;
        if (clientIterator == clientMap.end()) // New client
        {
            clientId = nextClient++;
            clientMap[client] = clientId;

            clientMutex->lock();
            (*clients)[clientId] = client;
            clientMutex->unlock();
        }
        else
        {
            clientId = clientIterator->second;
        }

        packetQueue->push(std::tuple<ClientId, Packet>(clientId, packet));

        packetMutex->unlock();
    }
}
