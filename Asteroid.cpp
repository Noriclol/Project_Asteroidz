#include "Asteroid.h"
#include <cstdlib>
#include <ctime>

Asteroid::Asteroid(int i) : Rigidbody()
{
    name = "Asteroid";
    srand(static_cast<unsigned int>(time(nullptr)) + i * i + i);

    float x = rand() % DISPLAY_WIDTH;
    float y = rand() % DISPLAY_HEIGHT;
    float vx = rand() % 100;
    float vy = rand() % 100;

    pos.x = x;
    pos.y = y;

    int random = rand() % 100;
    rotation_speed = static_cast<float>(random - 50) * 0.0005f;

    random = rand() % 100;
    scale = 1.0f + (static_cast<float>(random - 50) / 100.0f);

    radius = (scale * 12.0f);

    velocity.x = ((vx - 50) / 2.0f);
    velocity.y = ((vy - 50) / 2.0f);
}

void Asteroid::Simulate(float timeStep)
{
    Rigidbody::Simulate(timeStep);
    rotation += rotation_speed;
}

void Asteroid::Draw(SDL_Renderer* renderer)
{
    if (sprite)
    {

        SDL_Rect destRect = 
        {
        	static_cast<int>(pos.x) - static_cast<int>(25 * scale),
        	static_cast<int>(pos.y) - static_cast<int>(25 * scale),
        	static_cast<int>(50 * scale),
        	static_cast<int>(50 * scale)
        };
        SDL_RenderCopyEx(renderer, sprite, nullptr, &destRect, rotation, nullptr, SDL_FLIP_NONE);
    }
}