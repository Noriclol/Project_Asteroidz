#pragma once
#include <SDL.h>

class TimeManager
{
public:
    float currentGameTime;
    float deltaTime;
    Uint32 lastFrameTime;
    float startTimeOffset;


    TimeManager() : currentGameTime(0.0f), deltaTime(0.0f), lastFrameTime(0), startTimeOffset(0) {}

    void Update();

    float GetDeltaTime() const;

    float GetGameTime() const;

    void MarkStartTime();
};

