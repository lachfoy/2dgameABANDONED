#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class ResourceManager
{
public:
    ResourceManager(SDL_Renderer* renderer);
    ~ResourceManager();

    void loadGameResources();
    void loadFonts();

    SDL_Texture* getTexture(std::string key);
    TTF_Font* getFont(std::string key);
    
private:
    SDL_Renderer* renderer; // ptr to renderer for texture loading, resource manager does not have ownership
    std::map<std::string, SDL_Texture*> m_textures;
    std::map<std::string, TTF_Font*> m_fonts;

    SDL_Texture* loadTextureFromFile(const char* path, SDL_BlendMode blendMode);

};

#endif