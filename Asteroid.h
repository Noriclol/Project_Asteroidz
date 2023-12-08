#pragma once

#include "Rigidbody.h"
#include <memory>  // Include for std::shared_ptr
class Engine;

class Asteroid : public Rigidbody
{
public:
    std::shared_ptr<SDL_Texture> sprite = nullptr;  // Adjust this to use SDL2 textures
    float scale;
    float rotation_speed;
    bool hasEnteredScreen = false;

    Asteroid(Engine* engine);
    void Simulate(float timeStep) override;
    void Draw(SDL_Renderer* renderer) override;
};
