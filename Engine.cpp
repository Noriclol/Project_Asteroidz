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
	if (!Initialize_Renderer())
	{
		return false;
	}

	if (!Initialize_Managers())
	{
		return false;
	}

	//Loading Textures

    t_ship = LoadTexture("assets/Ship.bmp");
    t_asteroid = LoadTexture("assets/Asteroid.bmp");
    t_projectile = LoadTexture("assets/Projectile.bmp");
    t_background = LoadTexture("assets/Background.bmp");

	return true;
}

bool Engine::Initialize_Managers()
{
	timeManager = new TimeManager();
	return true;
}


bool Engine::Initialize_Renderer()
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



bool Engine::IsPositionOccupied(Vector2 pos, float radius)
{
    for (Rigidbody* obj : gameObjects)
    {
        float distance = (obj->pos - pos).Length();
        if (distance < (obj->radius + radius))
        {
            // The given position is too close to this object
            return true;
        }
    }
    return false;
}


bool Engine::SpawnScene()
{
	// Create player
	ship = new Ship();
	ship->sprite = t_ship;
	AddGameObject(ship);
	return true;
}



void Engine::SpawnWave(int wave)
{
    std::cout << "Spawning wave " << wave + 1 << std::endl;

    asteroidsDestroyedThisWave = 0;

    bool waveComplete = false;
    int asteroidsSpawned = 0;

    while (!waveComplete)
    {
        if(asteroidsSpawned == WAVE_BASE_COUNT + waveCount * WAVE_INCREMENT)
	        waveComplete = true;

        else
        {
        	if (timeSinceLastSpawn + timeManager->GetGameTime() > timeSinceLastSpawn + spawnDelay)
        	{
        		SpawnAsteroid();
				timeSinceLastSpawn = timeManager->GetGameTime();
				asteroidsSpawned++;
			}
        }
    }

    asteroidsCreatedThisWave = asteroidsSpawned;
    std::cout << "asteroidsCreatedThisWave: " << asteroidsCreatedThisWave << std::endl;
    waveCount++;
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



    //Keypress Response
	SDL_Event e;
    while (SDL_PollEvent(&e) != 0) 
    {
        if (e.type == SDL_QUIT) 
        {
            return false; // Exit the game loop
        }
        if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    return false; // Exit the game loop
                case SDLK_F1:
                    debug = !debug;
                    break;
                case SDLK_SPACE:
                    if (gameState == GameState::READY)
                    {
                        gameState = GameState::RUNNING;
                        this->timeManager->MarkStartTime();
                        //std::cout << "StartTimeOffset: " << this->timeManager->startTimeOffset << std::endl;
                    }
                    else if (!recentlyFired && gameState == GameState::RUNNING)
                    {
                        SpawnProjectile();
                        recentlyFired = true;
                        lastProjectileTime = this->timeManager->GetGameTime();
                    }
                    break;
                default:
                    break;
            }
        }
    }


	const Uint8* state = SDL_GetKeyboardState(nullptr);

    if (gameState == GameState::RUNNING)
    {

            //Projectile Cooldown
		if (this->timeManager->GetGameTime() - lastProjectileTime > PROJECTILE_COOLDOWN_DURATION)
		{
		    recentlyFired = false;
		}

    	//Reset input
	    ship->turn = 0;
	    ship->isThrusting = false;

	    if (state[SDL_SCANCODE_RIGHT])
	    {
	        ship->turn += 1;
	    }
	    if (state[SDL_SCANCODE_LEFT])
	    {
	        ship->turn -= 1;
	    }

	    if (state[SDL_SCANCODE_UP])
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

void Engine::SpawnProjectile()
{
	Projectile* projectile = new Projectile(ship->pos, ship->rotation, t_projectile);
	projectiles.push_back(projectile);
	AddGameObject(projectile);
}


void Engine::SpawnAsteroid()
{
	Asteroid* asteroid = new Asteroid(this);
	asteroid->sprite = t_asteroid;
	AddGameObject(asteroid);
    timeSinceLastSpawn = timeManager->GetGameTime();
}


void Engine::UpdateGameObjects(float elapsedTime)
{

    std::vector<Rigidbody*> objectsToDelete;

    // Collect objects marked for deletion
    for (Rigidbody* obj : gameObjects)
    {
        if(obj->markfordeletion)
        {
            objectsToDelete.push_back(obj);
        }
    }

    // Delete and remove the marked objects
    for (Rigidbody* obj : objectsToDelete)
    {
        gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
        
        if(obj->type == ObjectType::PROJECTILE)
        {
            projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), obj), projectiles.end());
        }
        // You can add similar checks for other object types if they have their own separate lists.
        
        delete obj;
    }

    // Simulate all objects in scene
    for (Rigidbody* obj : gameObjects)
    {
        obj->Simulate(elapsedTime);
        // std::cout << "Gameobject: " << obj->name << "\n pos: x_" << obj->pos.x << ": y_" << obj->pos.y << "\n velocity: x_" << obj->velocity.x << ": y_" << obj->velocity.y << std::endl;
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

void Engine::DrawGameObjects()
{
    for (Rigidbody* obj : gameObjects)
    {
        obj->Draw(renderer);
    }
}

void Engine::DrawDebug()
{
    for (Rigidbody* obj : gameObjects)
    {
        obj->DrawDebugCollider(renderer);
    }
}

void Engine::DrawGUI()
{

}

void Engine::Draw()
{
    DrawBackground();

    DrawGameObjects();

    DrawGUI();

    if(debug)
    {
	    DrawDebug();
    }
}




void Engine::CheckCollisions()
{
    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        for (size_t j = i + 1; j < gameObjects.size(); j++)
        {
            Rigidbody* objA = gameObjects[i];
            Rigidbody* objB = gameObjects[j];
            
            if (objA->IsColliding(*objB))
            {
                if ((objA->type == ObjectType::PROJECTILE && objB->type == ObjectType::ASTEROID) ||
                    (objA->type == ObjectType::ASTEROID && objB->type == ObjectType::PROJECTILE))
                {
                    // Mark both objects for deletion
                    objA->markfordeletion = true;
                    objB->markfordeletion = true;

                    asteroidsDestroyedThisWave++;
                    std::cout << "asteroidsDestroyed: " << asteroidsDestroyedThisWave << std::endl;

                    if(asteroidsDestroyedThisWave == asteroidsCreatedThisWave)
                    {
                        std::cout << "wave cleared" << std::endl;
                    	timeSinceLastWave = timeManager->GetGameTime();
					}
                }   
                else if (objA->type == ObjectType::ASTEROID && objB->type == ObjectType::ASTEROID)
                {
                    // Handle asteroid-asteroid collision
                    Vector2 delta = objA->pos - objB->pos;
                    float distance = delta.Length();

                    Vector2 normal = delta / distance;

                    float penetrationDepth = objA->radius + objB->radius - distance;

					if (penetrationDepth > 0) 
					{
						// Calculate how much each object should be moved
						Vector2 correction = normal * penetrationDepth / 2.0f; // Split the correction between the two objects

						// Adjust the positions of the two objects
						objA->pos += correction;
						objB->pos -= correction;
					}

                    Vector2 relativeVelocity = objA->velocity - objB->velocity;
                    float dot = relativeVelocity.Dot(normal);

                    // Compute the impulse magnitude considering the masses
                    float impulseMagnitude = 2.0 * (objA->mass * objB->mass) / (objA->mass + objB->mass) * dot;
                    Vector2 impulseA = (impulseMagnitude / objA->mass) * normal;
                    Vector2 impulseB = (impulseMagnitude / objB->mass) * normal;

                    objA->velocity -= impulseA;
                    objB->velocity += impulseB;
                }
                else if ((objA->type == ObjectType::ASTEROID && objB->type == ObjectType::SHIP) ||
						(objA->type == ObjectType::SHIP && objB->type == ObjectType::ASTEROID))
					 {
					    Rigidbody* asteroid;
					    Rigidbody* ship;

					    // Determine which object is the asteroid and which one is the ship
					    if (objA->type == ObjectType::ASTEROID)
					    {
					        asteroid = objA;
					        ship = objB;
					    }
					    else
					    {
					        asteroid = objB;
					        ship = objA;
					    }

					    // Handle asteroid-ship collision similar to asteroid-asteroid collision
					    Vector2 delta = asteroid->pos - ship->pos;
					    float distance = delta.Length();

					    Vector2 normal = delta / distance;


                        float penetrationDepth = objA->radius + objB->radius - distance;

						if (penetrationDepth > 0) 
						{
							// Calculate how much each object should be moved
							Vector2 correction = normal * penetrationDepth / 2.0f; // Split the correction between the two objects

							// Adjust the positions of the two objects

                            if(objA->type == ObjectType::ASTEROID)
                            {
                            	objA->pos += correction;
								objB->pos -= correction;
							}
							else
							{
								objA->pos -= correction;
								objB->pos += correction;
							}

						    Vector2 relativeVelocity = asteroid->velocity - ship->velocity;
						    float dot = relativeVelocity.Dot(normal);

						    // Compute the impulse magnitude considering the masses
						    float impulseMagnitude = 2.0 * (asteroid->mass * ship->mass) / (asteroid->mass + ship->mass) * dot;
						    Vector2 impulseAsteroid = (impulseMagnitude / asteroid->mass) * normal;
						    Vector2 impulseShip = (impulseMagnitude / ship->mass) * normal;

						    asteroid->velocity -= impulseAsteroid;
						    ship->velocity += impulseShip;
						}
					 }
	        }
	    }
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