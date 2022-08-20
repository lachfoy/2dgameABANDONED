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

    if (!m_fonts.empty())
    {
        // clear the fonts from the map
        printf("ResourceManager: deallocating fonts...\n");
        for (const auto& it : m_fonts)
        {
            printf("closing %s\n", it.first.c_str());
            TTF_CloseFont(it.second);
        }
    }
}

void ResourceManager::LoadGameTextures()
{
    printf("ResourceManager: loading textures...\n");
    m_textures["ShadowTexture"] = loadTextureFromFile("../images/Shadow.bmp", SDL_BLENDMODE_BLEND);
    m_textures["CrosshairTexture"] = loadTextureFromFile("../images/Crosshair.bmp", SDL_BLENDMODE_BLEND);
    m_textures["FireballTexture"] = loadTextureFromFile("../images/Fireball.bmp", SDL_BLENDMODE_BLEND);
    m_textures["base_particle_texture"] = loadTextureFromFile("../images/particle.bmp", SDL_BLENDMODE_BLEND);
    m_textures["spell_effect_texture"] = loadTextureFromFile("../images/spell_effect.bmp", SDL_BLENDMODE_ADD);
    m_textures["SmokeParticleTexture"] = loadTextureFromFile("../images/Smoke.bmp", SDL_BLENDMODE_BLEND);
    m_textures["FireballExplosionTexture"] = loadTextureFromFile("../images/FireballExplosion.bmp", SDL_BLENDMODE_BLEND);
    m_textures["SwordTexture"] = loadTextureFromFile("../images/Sword.bmp", SDL_BLENDMODE_BLEND);
    m_textures["SwordSlashTexture"] = loadTextureFromFile("../images/SwordSlash.bmp", SDL_BLENDMODE_BLEND);
}

void ResourceManager::loadFonts()
{
    printf("ResourceManager: loading fonts...\n");
    m_fonts["ArialBody"] = TTF_OpenFont("../fonts/arial.ttf", 21);
    m_fonts["ArialHeader"] = TTF_OpenFont("../fonts/arial.ttf", 34);
}

SDL_Texture* ResourceManager::getTexture(std::string key)
{
    SDL_Texture* texture = m_textures[key];
    if (!texture) printf("Error: texture \"%s\" does not exist\n", key.c_str());
    return texture;
}

TTF_Font* ResourceManager::getFont(std::string key)
{
    TTF_Font* font = m_fonts[key];
    if (!font) printf("Error: font \"%s\" does not exist\n", key.c_str());
    return font;
}

SDL_Texture* ResourceManager::loadTextureFromFile(const char* path, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE)
{
    SDL_Surface* surface = SDL_LoadBMP(path);
    if (!surface)
    {
        printf("Failed to load image %s\n", SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        printf("Failed to convert surface to texture %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    SDL_SetTextureBlendMode(texture, blendMode);

    printf("loaded %s\n", path);

    return texture;
}