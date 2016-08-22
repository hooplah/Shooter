#ifndef PACKETID_H_INCLUDED
#define PACKETID_H_INCLUDED

enum class ClientPacketId : sf::Uint8
{
    CONNECT,
    FOR_GAME_OBJECT, // game object's id, packet to send
    PLAYER_INPUT,
};

enum class ServerPacketId : sf::Uint8
{
    ACCEPT_CONNECT,
    SPAWN_YOU,
    SPAWN_OBJECT,
};

#endif // PACKETID_H_INCLUDED
