#include "Asteroid.h"
#include <cstdlib>
#include <ctime>
#include "Engine.h"



Asteroid::Asteroid(Engine* engine) : Rigidbody()
{

	this->type = ObjectType::ASTEROID;
    // Define the circle radius outside the screen space

    // Random angle for spawning on the circle
    float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * M_PI;

    // Calculate spawn position
    pos.x = SPAWN_RADIUS * cos(angle) + DISPLAY_WIDTH / 2;
    pos.y = SPAWN_RADIUS * sin(angle) + DISPLAY_HEIGHT / 2;


	// Define the target area size
    const float targetAreaSize = 300.0f; // The size of the target area
    const float halfArea = targetAreaSize / 2.0f;

    // Calculate direction towards the center of the screen
    Vector2 center(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
    Vector2 randomOffset((rand() % static_cast<int>(targetAreaSize)) - halfArea, 
                         (rand() % static_cast<int>(targetAreaSize)) - halfArea);

    Vector2 targetPosition = center + randomOffset;

    Vector2 direction = targetPosition - pos;
    direction.Normalize();

    // Set velocity towards the center
    float speed = 0.5f;
    velocity = direction * speed;

    // Set rotation speed and scale randomly
    rotation_speed = (rand() % 101 - 50) * 0.0005f;
    scale = 1.0f + (rand() % 101 - 50) / 100.0f;
    radius = (scale * 20.0f);

}

void Asteroid::Simulate(float timeStep)
{
    Rigidbody::Simulate(timeStep);
    if(hasEnteredScreen)
        Rigidbody::ScreenWrap();

    if(Rigidbody::ScreenWrapCheck())
    {
    	hasEnteredScreen = true;
	}

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