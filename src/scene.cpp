#include "scene.h"
#include <algorithm>

Scene::Scene(int screenWidth, int screenHeight) {
    // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
    squareRect.w = std::min(screenWidth, screenHeight) / 2;
    squareRect.h = std::min(screenWidth, screenHeight) / 2;

    // Square position: In the middle of the screen
    squareRect.x = screenWidth / 2 - squareRect.w / 2;
    squareRect.y = screenHeight / 2 - squareRect.h / 2;
}

Scene::~Scene() {}

void Scene::Update() {
}

void Scene::Render(SDL_Renderer* renderer) {
    // Clear screen (white)
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Draw square (red)
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &squareRect);

    SDL_RenderPresent(renderer);
}