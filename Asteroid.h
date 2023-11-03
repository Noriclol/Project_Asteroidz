#pragma once

#include "Rigidbody.h"

class Engine;

class Asteroid : public Rigidbody
{
public:
    SDL_Texture* sprite = nullptr;  // Adjust this to use SDL2 textures
    float scale;
    float rotation_speed;
    bool hasEnteredScreen = false;

    Asteroid(Engine* engine);
    void Simulate(float timeStep) override;
    void Draw(SDL_Renderer* renderer) override;
};
