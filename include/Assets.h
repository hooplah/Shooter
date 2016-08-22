#ifndef ASSETS_H
#define ASSETS_H

#include <map>

#include "SpriteInfo.h"

struct Assets
{
    static void loadAssets();
    static void loadSprite(const std::string& name, const std::string& path);

    static std::map<std::string, SpriteInfo> sprites;
};

#endif // ASSETS_H
