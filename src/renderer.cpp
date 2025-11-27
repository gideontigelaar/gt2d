#include "renderer.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Renderer::Renderer()
{
    window = SDL_CreateWindow(
        "GT2D",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screenSurface = SDL_GetWindowSurface(window);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::RenderScene()
{
    // Clear screen (white)
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Texture* tex = ResourceManager::GetInstance()->GetTexture("assets/Screenshot 2025-11-25 at 12.45.20.png", renderer);

    SDL_RenderCopy(renderer, tex, NULL, NULL);

    SDL_RenderPresent(renderer);
}

