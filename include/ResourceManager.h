#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include <SDL2/SDL.h>

class ResourceManager
{
public:
    ResourceManager(SDL_Renderer* renderer);
    ~ResourceManager();

    bool loadGameTextures();

    SDL_Texture* getTexture(std::string key);
    
private:
    SDL_Renderer* renderer; // ptr to renderer for texture loading, resource manager does not have ownership
    std::map<std::string, SDL_Texture*> textures;

    SDL_Texture* loadTextureFromFile(const char* path, SDL_BlendMode blendMode);

};

#endif