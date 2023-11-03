#include "TimeManager.h"

void TimeManager::Update()
{
	Uint32 currentTime = SDL_GetTicks();
	deltaTime = (currentTime - lastFrameTime) / 1000.0f;
	currentGameTime += deltaTime;
	lastFrameTime = currentTime;
}

float TimeManager::GetDeltaTime() const
{
	return deltaTime;
}

float TimeManager::GetGameTime() const
{
	return currentGameTime - startTimeOffset;
}

void TimeManager::MarkStartTime()
{
	startTimeOffset = currentGameTime;
}


