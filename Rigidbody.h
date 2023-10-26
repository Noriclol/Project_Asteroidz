#pragma once


#include <string>

#include "SDL.h"
#include "constants.h"

struct Vector2
{
	float x;
    float y;
};



class Rigidbody
{
public:
	std::string name;
    Vector2 pos;
    Vector2 velocity;
    Vector2 acceleration;
    float rotation;
    float radius;

    Rigidbody();

    virtual void Simulate(float timeStep);
    virtual bool IsColliding(const Rigidbody& other);
    virtual void Draw(SDL_Renderer* renderer) = 0;
};
