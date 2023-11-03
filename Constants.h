#pragma once

// Display constants
static const int DISPLAY_WIDTH = 800; 
static const int DISPLAY_HEIGHT = 600;  
const float SPAWN_RADIUS = sqrt(DISPLAY_WIDTH * DISPLAY_WIDTH + DISPLAY_HEIGHT * DISPLAY_HEIGHT) / 2 + 100; // 100 pixels outside the screen


// Asteroid constants
static const int ASTEROID_MAX_SCALE = 3;
static const int ASTEROID_MIN_SCALE = 1;
static const int ASTEROID_MASS_MULTIPLIER = 3;


// Wave constants
static const int WAVE_MAX_COUNT = 10;
static const int WAVE_BASE_COUNT = 3;
static const int WAVE_INCREMENT = 2;
static const float WAVE_DELAY = 10.0f;

// Ship constants
static const float SHIP_THRUST = 300.0f;
static const float SHIP_TURNSPEED = 300.0f;
static const float SHIP_DAMPING = 10.0f;

static const float PROJECTILE_COOLDOWN_DURATION = 0.5f;
static const float ASTEROID_COOLDOWN_DURATION = 0.75f;

// Maximum number of objects
static const int PROJECTILE_MAX_COUNT = 10;
static const int ASTEROID_MAX_COUNT = 50;


enum class ObjectType 
{
    SHIP,
	ASTEROID,
	PROJECTILE,
};

enum class GameState 
{
	LOADING,
	READY,
	RUNNING,
	UNLOADING,
};
