#include "Projectile.h"


Projectile::Projectile(const Vector2& shipPosition, float shipRotation, SDL_Texture* sprite)
{
    this->type = ObjectType::PROJECTILE;
    radius = 1;
    this->sprite = sprite;
    // Calculate the spawn position based on the ship's position and rotation.
    float spawnDistance = 30.0f;  // This defines how far in front of the ship the projectile spawns.
    float rotationRadians = shipRotation * (3.14159265 / 180.0); // Convert rotation from degrees to radians.
    pos.x = shipPosition.x + (spawnDistance * sin(rotationRadians));
    pos.y = shipPosition.y - (spawnDistance * cos(rotationRadians));
    
    // Set the velocity based on the ship's direction.
    float projectileSpeed = 300.0f;  // Speed of the projectile.
    velocity.x = projectileSpeed * sin(rotationRadians);
    velocity.y = -projectileSpeed * cos(rotationRadians);
}


void Projectile::Simulate(float timeStep)
{
	Rigidbody::Simulate(timeStep);
    if(ScreenWrap())
    {
		markfordeletion = true;
	}
}

bool Projectile::IsColliding(const Rigidbody& other)
{
	return Rigidbody::IsColliding(other);
}

void Projectile::Draw(SDL_Renderer* renderer)
{

    if (sprite)
    {
        SDL_Rect destRect = { (int)pos.x - 4, (int)pos.y - 4, 8, 8 };
        SDL_RenderCopyEx(renderer, sprite, nullptr, &destRect, rotation, nullptr, SDL_FLIP_NONE);
    }
}