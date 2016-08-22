#include "ShooterClient.h"

#include "Context.h"
#include "ClientPlayer.h"
#include "PacketId.h"
#include "WorldClient.h"

ShooterClient::ShooterClient(const std::string& serverAddr, unsigned short serverPort) : mSocket("0.0.0.0", 30001),
    mServerAddress(serverAddr), mServerPort(serverPort),
    mRunPacketThread(true)
{
    Packet packet;
    packet << ClientPacketId::CONNECT;
    send(packet);

    unsigned char buffer[1024];
    int packetSize = mSocket.recv(buffer, 1024);
    Packet recvPacket(buffer, packetSize);

    ServerPacketId packetId;
    recvPacket >> packetId;
    if (packetId != ServerPacketId::ACCEPT_CONNECT)
    {
        std::cout << "FAILED TO CONNECT TO SERVER\n";
        return;
    }

    std::cout << "Successfully connected to server\n";

    mPacketListener = std::thread(listenForPackets, &mSocket, &mPacketMutex, &mPacketQueue, &mRunPacketThread);
}

ShooterClient::~ShooterClient()
{
    mPacketMutex.lock();
    mRunPacketThread = false;
    mPacketMutex.unlock();
    mPacketListener.join();
}

void ShooterClient::update(Context& context, WorldClient& world)
{
    mPacketMutex.lock();
    while (!mPacketQueue.empty())
    {
        Packet packet = mPacketQueue.front();
        mPacketQueue.pop();

        ServerPacketId packetId;
        packet >> packetId;

        switch (packetId)
        {
            case ServerPacketId::SPAWN_YOU:
            {
                std::unique_ptr<GameObject> player = std::make_unique<ClientPlayer>(context, packet);
                world.addGameObject(std::move(player));
                break;
            }
        }
    }
    mPacketMutex.unlock();
}

void ShooterClient::send(const Packet& packet)
{
    mSocket.sendTo(packet.getData(), packet.getDataSize(), mServerAddress, mServerPort);
}

void ShooterClient::listenForPackets(UDPSocket* socket, std::mutex* packetMutex,
                                     std::queue<Packet>* packetQueue,
                                     bool* runPacketThread)
{
    unsigned char buffer[1024];
    while (true)
    {
        int packetSize = socket->recv(buffer, 1024);
        Packet packet(buffer, packetSize);

        packetMutex->lock();

        if (!*runPacketThread)
        {
            packetMutex->unlock();
            break;
        }

        packetQueue->push(packet);

        packetMutex->unlock();
    }
}
