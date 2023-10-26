#include "Engine.h"
#include <iostream>

Engine::~Engine()
{
	CleanScene();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) 
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) 
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}


bool Engine::SpawnScene()
{
    //Loading Textures

    SDL_Texture* t_ship = LoadTexture("assets/Ship.bmp");
    SDL_Texture* t_asteroid = LoadTexture("assets/Asteroid.bmp");
    t_background = LoadTexture("assets/Background.bmp");

	// Create player
	ship = new Ship();
	ship->sprite = t_ship;
	AddGameObject(ship);

	// Create asteroids
	for (int i = 0; i < 1; i++)
	{
		Asteroid* asteroid = new Asteroid(i);
		asteroid->sprite = t_asteroid;
		AddGameObject(asteroid);
	}
	return true;
}

bool Engine::CleanScene()
{
	for (Rigidbody* obj : gameObjects)
	{
		delete obj;
	}
    for (Projectile* prj : projectiles)
    {
	    delete prj;
    }
	gameObjects.clear();
	return true;
}

bool Engine::HandleInput()
{
    //Reset input
    ship->turn = 0;
    ship->isThrusting = false;


	SDL_Event e;
    while (SDL_PollEvent(&e) != 0) 
    {
        if (e.type == SDL_QUIT) 
        {
            return false; // Exit the game loop
        }


        const Uint8* state = SDL_GetKeyboardState(nullptr);

        if (state[SDL_SCANCODE_RIGHT])
        {
            ship->turn += 1;
            // Handle right arrow key press
        }
        if (state[SDL_SCANCODE_LEFT])
        {
            ship->turn -= 1;
        }

        if (state[SDL_SCANCODE_SPACE])
        {
            ship->isThrusting = true;
        }
    }
    return true;
}

void Engine::ClearScreen()
{
	SDL_SetRenderDrawColor(renderer, 5, 0, 100, 255); // Black background
    SDL_RenderClear(renderer);
}

void Engine::PresentScreen()
{
    SDL_RenderPresent(renderer);
}



void Engine::AddGameObject(Rigidbody* obj)
{
    gameObjects.push_back(obj);
}

void Engine::UpdateGameObjects(float elapsedTime)
{
    for (Rigidbody* obj : gameObjects)
    {
        obj->Simulate(elapsedTime);
        // std::cout << "Gameobject: " << obj->name << "\n pos: x_" << obj->pos.x << ": y_" << obj->pos.y << "\n velocity: x_" << obj->velocity.x << ": y_" << obj->velocity.y << std::endl;
    }
	


}

void Engine::DrawGameObjects()
{
    DrawBackground();  // Draw background
    for (Rigidbody* obj : gameObjects)
    {
        obj->Draw(renderer);
    }
}

void Engine::CheckCollisions()
{
    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        for (size_t j = i + 1; j < gameObjects.size(); j++)
        {
            if (gameObjects[i]->IsColliding(*gameObjects[j]))
            {
                // Handle collision response here, if needed
            }
        }
    }
}


void Engine::DrawBackground() 
{
    if (t_background) 
    {
        SDL_Rect destRect = {0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT};  // Cover the entire viewport
        SDL_RenderCopy(renderer, t_background, nullptr, &destRect);
    }
}


SDL_Texture* Engine::LoadTexture(const char* filepath) 
{
    // Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(filepath);
    if (!loadedSurface) 
    {
        printf("Unable to load image %s! SDL Error: %s\n", filepath, SDL_GetError());
        return nullptr;
    }

    // Convert surface to texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!texture) 
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", filepath, SDL_GetError());
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    return texture;
}