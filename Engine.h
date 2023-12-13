#pragma once

#ifndef ENGINE_H
#define ENGINE_H


#include "SDL.h"
#include <cstdio>
#include <vector>

#include "Singleton.h"

//Managers
#include "TimeManager.h"

//GameObjects
#include "Rigidbody.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Projectile.h"



class Engine : public Singleton
{
protected:
	Engine();

public:

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	static Engine* Instance() {
		if (instance == nullptr) {
			instance = new Engine();
		}
		return static_cast<Engine*>(instance);
	}





	// Renderer
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Managers
	TimeManager* timeManager = nullptr;

	//Textures
	SDL_Texture* t_ship = nullptr;
	SDL_Texture* t_asteroid = nullptr;
	SDL_Texture* t_projectile = nullptr;
    SDL_Texture* t_background = nullptr;

	//GameStates
	GameState gameState = GameState::LOADING;

	bool paused = false;
	bool debug = false;
	bool restart = false;

	//GameObjects

	Ship* ship = nullptr;
	std::vector<Projectile*> projectiles;  
	std::vector<Rigidbody*> gameObjects;

	float lastAsteroidTime = -ASTEROID_COOLDOWN_DURATION; // Initialize_Renderer to allow spawning immediately at game start
	float lastProjectileTime = -PROJECTILE_COOLDOWN_DURATION; // Initialize_Renderer to allow firing immediately at game start

	bool recentlyFired = false;


	int score = 0;
	int waveCount = 0;
	int asteroidsDestroyedThisWave = 0;
	int asteroidsCreatedThisWave = 0;
    float timeSinceLastSpawn = 0.0f;
    float timeSinceLastWave = 0.0f;

    // Define spawn and wave delays
    float spawnDelay = 1.0f; // Seconds between asteroid spawns
    float waveDelay = 5.0f;  // Seconds between waves

	// Initialization and shutdown
	~Engine();
	bool Initialize();
	bool Initialize_Managers();
	bool Initialize_Renderer();
	bool IsPositionOccupied(Vector2 pos, float radius);


	//Scene Management
	void SpawnWave(int wave);
	bool CleanScene();

	bool HandleInput();

	// Screen Management
	void ClearScreen();
	void PresentScreen();

	// Drawing
	void DrawBackground();
    void DrawGameObjects();
	void DrawDebug();
	void DrawGUI();

	void Draw();



	// GameObjects
    void AddGameObject(Rigidbody* obj);
	bool SpawnShip();
	void SpawnProjectile();
	void SpawnAsteroid();
	void UpdateGameObjects(float elapsedTime);
    void CheckCollisions();

	SDL_Texture* LoadTexture(const char* filepath);
};

#endif // ENGINE_H