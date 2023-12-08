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

bool Rigidbody::ScreenWrapCheck()
{
	// Screen wrapping logic
	if (pos.x > DISPLAY_WIDTH + radius)
	{
		return true;
	}
	else if (pos.x < -radius)
	{
		return true;
	}

	if (pos.y > DISPLAY_HEIGHT + radius)
	{
		return true;
	}
	else if (pos.y < -radius)
	{
		return true;
	}
	return false;
}

bool Rigidbody::ScreenWrap()
{
	// Screen wrapping logic
    if (pos.x > DISPLAY_WIDTH + radius)
    {
        pos.x = -radius;
    	return true;
    }
    else if (pos.x < -radius)
    {
        pos.x = DISPLAY_WIDTH + radius;
        return true;
    }

    if (pos.y > DISPLAY_HEIGHT + radius)
    {
        pos.y = -radius;
        return true;
    }
    else if (pos.y < -radius)
    {
        pos.y = DISPLAY_HEIGHT + radius;
        return true;
    }
    return false;
}



inline bool Rigidbody::IsColliding(const Rigidbody& other)
{
    float xDiff = pos.x - other.pos.x;
    float yDiff = pos.y - other.pos.y;
    float radii = radius + other.radius;

    //if (abs(xDiff) > radii || abs(yDiff) > radii) {
    //    return false;
    //}


    return (xDiff * xDiff) + (yDiff * yDiff) < radii * radii;
}

void Rigidbody::DrawDebugCollider(SDL_Renderer* renderer)
{
    int x = static_cast<int>(pos.x);
    int y = static_cast<int>(pos.y);
    int r = static_cast<int>(radius);

    // Set the color for the debug collider (e.g., red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw the circle using SDL's ellipse drawing function. 
    // Note: SDL doesn't have a direct circle drawing function, so we use the ellipse function.
    for (int i = y - r; i < y + r; i++)
    {
        int length = static_cast<int>(sqrt(r * r - (i - y) * (i - y)));
        SDL_RenderDrawLine(renderer, x - length, i, x + length, i);
    }

    // Reset render color to default (e.g., white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
