#pragma once
#include "RigidBody.h"

class Projectile : public Rigidbody
{

	void Simulate(float timeStep) override;
    bool IsColliding(const Rigidbody& other) override;
    void Draw(SDL_Renderer* renderer) override;

};

