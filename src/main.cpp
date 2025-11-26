#include <iostream>
#include <algorithm>
#include <chrono>

#include <SDL.h>
#include "scene.h"
#include "renderer.h"

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    if(SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
        std::cout << "SDL could not be initialized!" << std::endl
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        std::cout << "Could not create window: " << IMG_GetError( ) << std::endl;
        return 1;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0")) {
        std::cout << "SDL can not disable compositor bypass!" << std::endl;
        return 0;
    }
#endif

    Renderer *renderer = new Renderer();
    if(!renderer) 
    {
        std::cout << "Renderer could not be created!" << std::endl
                  << "SDL_Error: " << SDL_GetError() << std::endl;
    } 
    else 
    {
        Scene* scene = new Scene(800, 600);

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
            scene->Update(deltaTime);
            renderer->RenderScene();
            auto frameEnd = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float>(frameEnd - frameStart).count();
            if(frameTime < TARGET_FRAME_TIME) {
                SDL_Delay(static_cast<Uint32>((TARGET_FRAME_TIME - frameTime) * 1000.0f));
            }
            frameStart = std::chrono::high_resolution_clock::now();
        }
        delete renderer;
    }

    SDL_Quit();

    return 0;
}