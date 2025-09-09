#include <iostream>
#include <algorithm>
#include <chrono>

#include <SDL.h>
#include "scene.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized!" << std::endl
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0")) {
        std::cout << "SDL can not disable compositor bypass!" << std::endl;
        return 0;
    }
#endif

    SDL_Window *window = SDL_CreateWindow(
        "Basic C++ SDL project",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if(!window) {
        std::cout << "Window could not be created!" << std::endl
                  << "SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer) {
            std::cout << "Renderer could not be created!" << std::endl
                      << "SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            Scene scene(SCREEN_WIDTH, SCREEN_HEIGHT);

            bool quit = false;

            const float TARGET_FPS = 60.0f;
            const float TARGET_FRAME_TIME = 1.0f / TARGET_FPS;
            const float MAX_DELTA_TIME = 0.1f;

            auto frameStart = std::chrono::high_resolution_clock::now();
            auto lastTime = frameStart;

            while(!quit) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
                lastTime = currentTime;

                deltaTime = std::min(deltaTime, MAX_DELTA_TIME);

                SDL_Event e;
                while(SDL_PollEvent(&e)) {
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                scene.Update(deltaTime);
                scene.Render(renderer);

                auto frameEnd = std::chrono::high_resolution_clock::now();
                float frameTime = std::chrono::duration<float>(frameEnd - frameStart).count();

                if(frameTime < TARGET_FRAME_TIME) {
                    SDL_Delay(static_cast<Uint32>((TARGET_FRAME_TIME - frameTime) * 1000.0f));
                }

                frameStart = std::chrono::high_resolution_clock::now();
            }

            SDL_DestroyRenderer(renderer);
        }

        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}