#include "resourcemanager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
    std::map<std::string, SDL_Texture*>::iterator text_it;
    for (text_it=_textures.begin(); text_it!=_textures.end(); ++text_it)
    {
        if (text_it->second != nullptr)
        {
            SDL_DestroyTexture(_textures[text_it->first]);
            _textures[text_it->first] = nullptr;
        }
    }
    _textures.clear();
}

ResourceManager* ResourceManager::GetInstance()
{
    if(_instance == nullptr) _instance = new ResourceManager();

    return _instance;
}

SDL_Texture* ResourceManager::GetTexture(std::string fileName, SDL_Renderer* renderer)
{
    if (_textures[fileName]) { return _textures[fileName]; }

    SDL_Surface* img = IMG_Load(fileName.c_str());
    if (!img) 
    {
        std::cout << "ResourceManager line: 24" << "\n";
        std::cout << "IMG_Load error: " << IMG_GetError() << "\n";
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    if (!tex) 
    {
        std::cout << "ResourceManager line: 32" << "\n";
        std::cout << "Texture error: " << SDL_GetError() << "\n";
        return nullptr;
    }

    _textures[fileName] = tex;

    std::cout << fileName << "\n";
    return tex;
}

ResourceManager* ResourceManager::_instance = nullptr;