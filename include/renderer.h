#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

#include "scene.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void RenderScene();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Surface* screenSurface;
};

#endif