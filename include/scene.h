#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

class Scene {
public:
    Scene(int screenWidth, int screenHeight);
    ~Scene();

    void Update(float deltaTime);

    void Render(SDL_Renderer* renderer);

private:
    SDL_Rect squareRect;
};

#endif // SCENE_H