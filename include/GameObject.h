#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <cstddef>
#include <vector>

#include "SFML/System/Time.hpp"

#include "Packet.h"

class Context;

typedef std::size_t ClientId;

class GameObject
{
    public:
        virtual void serialize(Context& context, Packet& packet) = 0;
        virtual void update(Context& context, sf::Time dt) = 0;
        virtual void rewindTicks(Context& context, std::size_t ticksBack) = 0;
        virtual void playTick(Context& context, std::size_t ticksBack) = 0;
        virtual void handlePacket(Packet& packet) = 0;

        const std::vector<Packet>& getPacketsToSend() const {return mPacketsToSend;}
        ClientId& getId(){return mId;}

    protected:
        void sendPacket(const Packet& packet) {mPacketsToSend.push_back(packet);}

    private:
        ClientId mId;
        std::vector<Packet> mPacketsToSend;
};

#endif // GAMEOBJECT_H
