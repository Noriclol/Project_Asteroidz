#pragma once

static const int DISPLAY_WIDTH = 800; 
static const int DISPLAY_HEIGHT = 600;  

static const float SHIP_THRUST = 2000.0f;
static const float SHIP_TURNSPEED = 3000.0f;
static const float SHIP_DAMPING = 10.0f;

static const int ASTEROID_COUNT = 50;

enum class ObjectType 
{
    Type_Ship,
    Type_Asteroid
};

enum class GameState 
{
    State_Run,
    State_Restart
};
