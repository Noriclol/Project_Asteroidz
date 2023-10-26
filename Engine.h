#pragma once
#include "SDL.h"
#include <cstdio>
#include <vector>

#include "Rigidbody.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Projectile.h"

class Engine
{
public:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

    SDL_Texture* t_background = nullptr;

	Ship* ship = nullptr;

	std::vector<Projectile*> projectiles;  // List of projectiles
	std::vector<Rigidbody*> gameObjects;  // List of game objects

	~Engine();

	bool Initialize();
	bool SpawnScene();
	bool CleanScene();

	bool HandleInput();

	void ClearScreen();
	void PresentScreen();


    void AddGameObject(Rigidbody* obj);
    void UpdateGameObjects(float elapsedTime);
    void DrawGameObjects(); 
    void CheckCollisions();
	void DrawBackground();
	SDL_Texture* LoadTexture(const char* filepath);
};

