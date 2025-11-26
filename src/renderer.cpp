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

    SDL_Surface* img = IMG_Load("assets/Screenshot 2025-11-25 at 12.45.20.png");
    if (!img) {
        std::cout << "IMG_Load error: " << IMG_GetError() << "\n";
        return;
    }

    // Convert surface → texture
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img); // surface kan weg

    if (!tex) {
        std::cout << "Texture error: " << SDL_GetError() << "\n";
        return;
    }

    // Render de texture
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_DestroyTexture(tex);

    // Present result
    SDL_RenderPresent(renderer);
}

