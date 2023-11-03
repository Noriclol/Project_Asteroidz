#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "Engine.h"
#include "Ship.h"

Engine* engine = nullptr;



void StartText()
{
	std::cout << "Welcome to Asteroids!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "W - Thrust" << std::endl;
    std::cout << "A - Rotate Left" << std::endl;
    std::cout << "D - Rotate Right" << std::endl;
    std::cout << "Space - Fire" << std::endl;
    std::cout << "##################" << std::endl;
    std::cout << "Press Space to Start" << std::endl;
}


void Run() {

    bool isRunning = true;

    

    while (isRunning) 
    {
		engine->ClearScreen();


    	switch(engine->gameState)
        {
    		case GameState::LOADING:

    			StartText();
    			engine->SpawnScene();
				engine->gameState = GameState::READY;
	            break;

            case GameState::READY:

                isRunning = engine->HandleInput();
    			engine->Draw();
	            break;

            case GameState::RUNNING:


                if(engine->timeManager->GetGameTime() > engine->timeSinceLastWave + engine->waveDelay && 
                    engine->asteroidsDestroyedThisWave == engine->asteroidsCreatedThisWave)
                {
					engine->SpawnWave(engine->waveCount);
                }

				isRunning = engine->HandleInput();
				engine->timeManager->Update();

				engine->CheckCollisions();
                engine->UpdateGameObjects(engine->timeManager->GetDeltaTime());
				
				engine->Draw();

	            break;

            case GameState::UNLOADING:

	            break;

	        default: 
	            break;
        }

        engine->PresentScreen(); 
    }
}




int main(int argc, char* argv[])
{
	engine = new Engine();

    if (!engine->Initialize()) 
    {
        printf("Failed to initialize!\n");
        delete engine; 
        return 1;
    }
    

    Run();

    delete engine;
	return 0;
}
