#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class ResourceManager
{
public:
    ~ResourceManager();

    static ResourceManager* GetInstance();

    SDL_Texture* GetTexture(std::string fileName, SDL_Renderer* renderer);
private:
    static ResourceManager* _instance;
    ResourceManager();

    std::map<std::string, SDL_Texture*> _textures;
};

#endif