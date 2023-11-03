#pragma once
#include "RigidBody.h"

class Projectile : public Rigidbody
{
public:
	
	SDL_Texture* sprite = nullptr;  



	Projectile(const Vector2& shipPosition, float shipRotation, SDL_Texture* sprite);
	void Simulate(float timeStep) override;
    bool IsColliding(const Rigidbody& other) override;
    void Draw(SDL_Renderer* renderer) override;
};

