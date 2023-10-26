#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "Engine.h"
#include "Ship.h"

Engine* engine = nullptr;


void Run() {



    bool isRunning = true;

    std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point currentTime;
    std::chrono::duration<float> elapsedTime;
    while (isRunning) 
    {
        isRunning = engine->HandleInput();

        //Time
		currentTime = std::chrono::high_resolution_clock::now();
		elapsedTime = currentTime - lastTime;
		float deltaTime = elapsedTime.count();
    	lastTime = currentTime;

        //Engine
        engine->ClearScreen();

        engine->UpdateGameObjects(deltaTime);
        engine->CheckCollisions();
        engine->DrawGameObjects();

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

    engine->SpawnScene();

    Run();

    delete engine;
	return 0;
}
