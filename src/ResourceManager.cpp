#include "ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

ResourceManager::~ResourceManager()
{
    if (!m_textures.empty())
    {
        // clear the textures from the map
        printf("ResourceManager: deallocating textures...\n");
        for (const auto& it : m_textures)
        {
            printf("destroying %s\n", it.first.c_str());
            SDL_DestroyTexture(it.second);
        }
    }
}

bool ResourceManager::loadGameResources()
{
    printf("ResourceManager: loading textures...\n");
    m_textures["ShadowTexture"] = loadTextureFromFile("../images/Shadow.bmp", SDL_BLENDMODE_BLEND);
    m_textures["CrosshairTexture"] = loadTextureFromFile("../images/Crosshair.bmp", SDL_BLENDMODE_BLEND);
    m_textures["FireballTexture"] = loadTextureFromFile("../images/Fireball.bmp", SDL_BLENDMODE_BLEND);
    m_textures["FireballParticleTexture"] = loadTextureFromFile("../images/Fireball.bmp", SDL_BLENDMODE_BLEND);
    m_textures["SmokeParticleTexture"] = loadTextureFromFile("../images/Smoke.bmp", SDL_BLENDMODE_BLEND);
    m_textures["FireballExplosionTexture"] = loadTextureFromFile("../images/FireballExplosion.bmp", SDL_BLENDMODE_BLEND);
    m_textures["SwordTexture"] = loadTextureFromFile("../images/Sword.bmp", SDL_BLENDMODE_BLEND);
    m_textures["SwordSlashTexture"] = loadTextureFromFile("../images/SwordSlash.bmp", SDL_BLENDMODE_BLEND);

    return true;
}

SDL_Texture* ResourceManager::getTexture(std::string key)
{
    return m_textures[key];
}

SDL_Texture* ResourceManager::loadTextureFromFile(const char* path, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE)
{
    bool success; // not used rn

    SDL_Surface* surface = SDL_LoadBMP(path);
    if (!surface)
    {
        printf("Failed to load image %s\n", SDL_GetError());
        success = false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        printf("Failed to convert surface to texture %s\n", SDL_GetError());
        success = false;
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    SDL_SetTextureBlendMode(texture, blendMode);

    printf("loaded %s\n", path);

    return texture;
}