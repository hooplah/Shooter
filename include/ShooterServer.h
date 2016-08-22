#ifndef SHOOTERSERVER_H
#define SHOOTERSERVER_H

#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>

#include "Socket.h"
#include "Packet.h"

struct Context;
class WorldServer;

struct ClientHandle
{
    bool operator<(const ClientHandle& other) const
    {
        if (mPort < other.mPort)
            return true;
        else if (mPort > other.mPort)
            return false;
        else
        {
            if (mAddress < other.mAddress)
                return true;
            else
                return false;
        }
    }

    std::string mAddress;
    unsigned short mPort;
};

typedef std::size_t ClientId;

class ShooterServer
{
    public:
        ShooterServer();
        ~ShooterServer();

        void update(Context& context, WorldServer& world);

        void send(const Packet& packet, ClientId& client);

    private:
        static void listenForPackets(UDPSocket* socket, std::mutex* packetMutex,
                                     std::queue<std::tuple<ClientId, Packet>>* packetQueue,
                                     bool* runPacketThread,
                                     std::mutex* clientMutex, std::map<ClientId, ClientHandle>* clients);

        UDPSocket mSocket;

        std::mutex mPacketMutex;
        std::queue<std::tuple<ClientId, Packet>> mPacketQueue;
        bool mRunPacketThread;

        std::mutex mClientMutex; // Guards mClients
        std::map<ClientId, ClientHandle> mClients;

        std::thread mPacketListener;
};

#endif // SHOOTERSERVER_H
