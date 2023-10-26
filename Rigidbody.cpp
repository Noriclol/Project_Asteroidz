#include "Rigidbody.h"


Rigidbody::Rigidbody()
{
    pos.x = 0;
    pos.y = 0;
    velocity.x = 0;
    velocity.y = 0;
    acceleration.x = 0;
    acceleration.y = 0;
    rotation = 0.0f;
    radius = 1.0f;
}

void Rigidbody::Simulate(float timeStep)
{
    pos.x += (velocity.x * timeStep);
    pos.y += (velocity.y * timeStep);
    velocity.x += (acceleration.x * timeStep);
    velocity.y += (acceleration.y * timeStep);
}

bool Rigidbody::IsColliding(const Rigidbody& other)
{
    int xDiff = pos.x - other.pos.x;
    int yDiff = pos.y - other.pos.y;
    int radii = radius + other.radius;

    return (xDiff * xDiff) + (yDiff * yDiff) < radii * radii;
}