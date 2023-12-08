#pragma once

#include "Rigidbody.h"
#include <memory>  // Include for std::shared_ptr
class Ship : public Rigidbody
{
public:
    std::shared_ptr<SDL_Texture> sprite = nullptr;  // Adjust this to use SDL2 textures
    bool isThrusting;
    int turn;

    Ship();
    void Simulate(float timeStep) override;
    bool IsColliding(const Rigidbody& other) override;
    void Draw(SDL_Renderer* renderer) override;
};