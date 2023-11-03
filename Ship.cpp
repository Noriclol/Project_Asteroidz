#include "Ship.h"

#include <ctime>
#include <iostream>

#include "SDL_keycode.h"

Ship::Ship() : Rigidbody()
{
    this->type = ObjectType::SHIP;
    pos.x = DISPLAY_WIDTH / 2;
    pos.y = DISPLAY_HEIGHT / 2;
    radius = 20;
    isThrusting = false;
	turn = 0;
}

void Ship::Simulate(float timeStep)
{
    float rotation_addition = (float)turn * SHIP_TURNSPEED * timeStep;
    if (rotation + rotation_addition > 360.0f)
    {
        rotation = rotation += rotation_addition - 360.0f;
    }
	else if (rotation + rotation_addition < 0.0f)
    {
        rotation = rotation += rotation_addition + 360.0f;
    }
    else
    {
		rotation += rotation_addition;
    }


    if (isThrusting)
    {
        float rotationRadians = rotation * (3.14159265 / 180.0); // Convert rotation from degrees to radians
        acceleration.x += (SHIP_THRUST * sin(rotationRadians));
        acceleration.y -= (SHIP_THRUST * cos(rotationRadians)); 
        //std::cout << "rotation: " << rotation << std::endl;
    }

    Rigidbody::Simulate(timeStep);
    Rigidbody::ScreenWrap();

    acceleration.x = 0;
    acceleration.y = 0;


    // Apply damping to velocity
    velocity.x *= (1.0 - timeStep / SHIP_DAMPING);
    velocity.y *= (1.0 - timeStep / SHIP_DAMPING);

    // If velocity is below a certain threshold, set it to zero
    if (fabs(velocity.x) < 0.01) velocity.x = 0;
    if (fabs(velocity.y) < 0.01) velocity.y = 0;
}

bool Ship::IsColliding(const Rigidbody& other)
{
    bool colliding = Rigidbody::IsColliding(other);
    //if (colliding)
    //{
    //    // Reset ship position and state if colliding
    //    pos.x = DISPLAY_WIDTH / 2;
    //    pos.y = DISPLAY_HEIGHT / 2;
    //    rotation = 0.0f;
    //    velocity.x = 0;
    //    velocity.y = 0;
    //}
    return colliding;
}

void Ship::Draw(SDL_Renderer* renderer)
{
    if (sprite)
    {
        SDL_Rect destRect = { (int)pos.x - 25, (int)pos.y - 25, 50, 50 };
        SDL_RenderCopyEx(renderer, sprite, nullptr, &destRect, rotation, nullptr, SDL_FLIP_NONE);
    }
}