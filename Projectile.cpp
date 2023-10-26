#include "Projectile.h"

void Projectile::Simulate(float timeStep)
{
	Rigidbody::Simulate(timeStep);
}

bool Projectile::IsColliding(const Rigidbody& other)
{
	return Rigidbody::IsColliding(other);
}

void Projectile::Draw(SDL_Renderer* renderer)
{
}
