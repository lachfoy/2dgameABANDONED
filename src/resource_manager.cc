#include "resource_manager.h"

ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
    renderer_ = renderer;
}

ResourceManager::~ResourceManager()
{
    if (!textures_.empty())
    {
        // clear the textures from the map
        printf("ResourceManager: deallocating textures...\n");
        for (const auto& it : textures_)
        {
            printf("destroying %s\n", it.first.c_str());
            SDL_DestroyTexture(it.second);
        }
    }
    textures_.clear();

    if (!fonts_.empty())
    {
        // clear the fonts from the map
        printf("ResourceManager: deallocating fonts...\n");
        for (const auto& it : fonts_)
        {
            printf("closing %s\n", it.first.c_str());
            TTF_CloseFont(it.second);
        }
    }
    fonts_.clear();

    if (!sounds_.empty())
    {
        // clear the fonts from the map
        printf("ResourceManager: deallocating sounds...\n");
        for (const auto& it : sounds_)
        {
            printf("freeing %s\n", it.first.c_str());
            Mix_FreeChunk(it.second);
        }
    }
    sounds_.clear();
}

void ResourceManager::LoadGameTextures()
{
    printf("ResourceManager: loading textures...\n");
    textures_["background_forest_texture"] = LoadTextureFromFile("../resources/textures/background_forest.png", SDL_BLENDMODE_NONE);
    textures_["fireball_texture"] = LoadTextureFromFile("../resources/textures/fireball.png", SDL_BLENDMODE_BLEND);
    textures_["flame_particle2_texture"] = LoadTextureFromFile("../resources/textures/flame_particle2.png", SDL_BLENDMODE_ADD);
    textures_["player_texture"] = LoadTextureFromFile("../resources/textures/player.png", SDL_BLENDMODE_BLEND);
    textures_["shadow_texture"] = LoadTextureFromFile("../resources/textures/shadow.png", SDL_BLENDMODE_BLEND);
    textures_["skeleton_texture"] = LoadTextureFromFile("../resources/textures/skeleton.png", SDL_BLENDMODE_BLEND);
    textures_["slime_texture"] = LoadTextureFromFile("../resources/textures/slime.png", SDL_BLENDMODE_BLEND);
}

void ResourceManager::LoadFonts()
{
    printf("ResourceManager: loading fonts...\n");
    fonts_["debug_font"] = TTF_OpenFont("../resources/fonts/arial.ttf", 16);
}

void ResourceManager::LoadSounds()
{
    printf("ResourceManager: loading sounds...\n");
    sounds_["fireball_sound"] = Mix_LoadWAV("../resources/sounds/fireball.wav");
    if (sounds_["fireball_sound"] == NULL) printf("OOOOPSIES WOOPSIES\n");
    sounds_["fireball_explosion_sound"] = Mix_LoadWAV("../resources/sounds/fireball_explosion.wav");
}

SDL_Texture* ResourceManager::GetTexture(std::string key)
{
    SDL_Texture* texture = textures_[key];
    if (!texture) printf("Error: texture \"%s\" does not exist\n", key.c_str());
    return texture;
}

TTF_Font* ResourceManager::GetFont(std::string key)
{
    TTF_Font* font = fonts_[key];
    if (!font) printf("Error: font \"%s\" does not exist\n", key.c_str());
    return font;
}

Mix_Chunk* ResourceManager::GetSound(std::string key)
{
    Mix_Chunk* sound = sounds_[key];
    if (!sound) printf("Error: sound \"%s\" does not exist\n", key.c_str());
    return sound;
}

SDL_Texture* ResourceManager::LoadTextureFromFile(const char* path, SDL_BlendMode blend_mode = SDL_BLENDMODE_NONE)
{
    SDL_Surface* surface = IMG_Load(path);
    if (!surface)
    {
        printf("Failed to load image %s\n", SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (!texture)
    {
        printf("Failed to convert surface to texture %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    SDL_SetTextureBlendMode(texture, blend_mode);

    printf("loaded %s\n", path);

    return texture;
}