#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "Engine.h"
#include "Ship.h"

//Engine* engine = nullptr;


// Instructions for the player meant to be displayed in the console
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


    Engine* engine = Engine::Instance();
    bool isRunning = true;
    while (isRunning) 
    {
		engine->ClearScreen();


    	switch(engine->gameState)
        {
    		case GameState::LOADING:

                //BOOTING THE GAME
    			StartText();
    			engine->SpawnShip();
				engine->gameState = GameState::READY;
	            break;

            case GameState::READY:
                // handle input so we can start game
                isRunning = engine->HandleInput();

                //Drawcall
    			engine->Draw();
	            break;

            case GameState::RUNNING:

                // wave check
                if(engine->timeManager->GetGameTime() > engine->timeSinceLastWave + engine->waveDelay && 
                    engine->asteroidsDestroyedThisWave == engine->asteroidsCreatedThisWave)
                {
					engine->SpawnWave(engine->waveCount);
                }
                //handling input and setting isRunning to false if the right keystroke is detected
				isRunning = engine->HandleInput();
                
                //update time
				engine->timeManager->Update();

                //check collisions and applying the delta time to gameobjects.
				engine->CheckCollisions();
                engine->UpdateGameObjects(engine->timeManager->GetDeltaTime());
				
                //Drawcall
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

    //engine = new Engine();

    Engine* engine = Engine::Instance();

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
