#include "ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

ResourceManager::~ResourceManager()
{
    // clear the textures from the map
    for (const auto& it : textures)
    {
        printf("destroying %s\n", it.first.c_str());
        SDL_DestroyTexture(it.second);
    }
}

bool ResourceManager::loadTextures() // in future this could take a list of paths and iterate through that.\
    this way, the game manages which textures it wants, rather than hardcoding them.
{
    textures["FireballTexture"] = loadTextureFromFile("../images/Fireball.bmp");

    return true;
}

SDL_Texture* ResourceManager::getTexture(std::string key)
{
    return textures[key];
}

SDL_Texture* ResourceManager::loadTextureFromFile(const char* path)
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

    return texture;
}