#pragma once


#include <string>

#include "SDL.h"
#include "constants.h"

//homemade vector2 
struct Vector2
{
    float x;
    float y;

    // Constructors
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}

    // Overload + and - for addition and subtraction
    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    // Overload * for scalar multiplication
    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    // Overload / for scalar division
    Vector2 operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    // Compute magnitude (length) of the vector
    float Length() const
    {
        return sqrt(x * x + y * y);
    }

    // Normalize the vector (make it unit length)
    Vector2 Normalize() const
    {
        float len = Length();
        if (len > 0.0f)
            return (*this) / len;
        return *this;
    }

    // Dot product with another vector
    float Dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

	Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    // In-place subtraction
    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

	Vector2& operator*=(float scalar)
    {
    	x *= scalar;
		y *= scalar;
		return *this;
	}
};

inline Vector2 operator*(float lhs, const Vector2& rhs)
{
    return Vector2(lhs * rhs.x, lhs * rhs.y);
}

// Base Rigidbody Gameobject
class Rigidbody
{
public:
	ObjectType type;
    Vector2 pos;
    Vector2 velocity;
    Vector2 acceleration;
    float rotation = 0;
    float radius = 1;
    float mass = ASTEROID_MASS_MULTIPLIER * radius;
	bool markfordeletion = false;

    Rigidbody();

    virtual void Simulate(float timeStep);
	bool ScreenWrapCheck();
	bool ScreenWrap();
	virtual bool IsColliding(const Rigidbody& other);
    virtual void Draw(SDL_Renderer* renderer) = 0;
	void DrawDebugCollider(SDL_Renderer* renderer);
};
