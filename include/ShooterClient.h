#ifndef SHOOTERCLIENT_H
#define SHOOTERCLIENT_H

#include <mutex>
#include <queue>
#include <thread>

#include "Socket.h"
#include "Packet.h"

struct Context;
class WorldClient;

class ShooterClient
{
    public:
        ShooterClient(const std::string& serverAddr, unsigned short serverPort);
        ~ShooterClient();

        void update(Context& context, WorldClient& world);

        void send(const Packet& packet);

    private:
        static void listenForPackets(UDPSocket* socket, std::mutex* packetMutex,
                                     std::queue<Packet>* packetQueue,
                                     bool* runPacketThread);

        UDPSocket mSocket;
        std::string mServerAddress;
        unsigned short mServerPort;

        std::mutex mPacketMutex;
        std::queue<Packet> mPacketQueue;
        bool mRunPacketThread;

        std::thread mPacketListener;
};

#endif // SHOOTERCLIENT_H
