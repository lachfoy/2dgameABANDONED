#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class ResourceManager
{
public:
    ResourceManager(SDL_Renderer* renderer);
    ~ResourceManager();

    void LoadGameTextures();
    void LoadFonts();

    SDL_Texture* GetTexture(std::string key);
    TTF_Font* GetFont(std::string key);
    
private:
    SDL_Renderer* renderer_; // ptr to renderer for texture loading, resource manager does not have ownership
    std::map<std::string, SDL_Texture*> textures_;
    std::map<std::string, TTF_Font*> fonts_;

    SDL_Texture* LoadTextureFromFile(const char* path, SDL_BlendMode blend_mode);

};

#endif