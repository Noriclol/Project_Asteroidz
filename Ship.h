#pragma once

#include "Rigidbody.h"

class Ship : public Rigidbody
{
public:
    SDL_Texture* sprite = nullptr;  // Adjust this to use SDL2 textures
    bool isThrusting;
    int turn;

    Ship();
    void Simulate(float timeStep) override;
    bool IsColliding(const Rigidbody& other) override;
    void Draw(SDL_Renderer* renderer) override;
};