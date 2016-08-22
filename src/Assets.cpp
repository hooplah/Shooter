#include "Assets.h"

std::map<std::string, SpriteInfo> Assets::sprites;

void Assets::loadAssets()
{
    loadSprite("ammocrate", "Content/Textures/ammocrate.png");
}

void Assets::loadSprite(const std::string& name, const std::string& path)
{
    sprites[name] = SpriteInfo(name, path);
}
