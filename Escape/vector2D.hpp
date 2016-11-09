#pragma once

#include <iostream>

struct Vector2D
{
	float x;
	float y;

	Vector2D();
	Vector2D(const float &pX, const float &pY);

	Vector2D operator+(const Vector2D &pOtherVector);
	Vector2D operator-(const Vector2D &pOtherVector);
	Vector2D operator*(const Vector2D &pOtherVector);
	Vector2D operator/(const Vector2D &pOtherVector);
	Vector2D operator=(const Vector2D &pOtherVector);
	Vector2D operator+=(const Vector2D &pOtherVector);
	Vector2D operator-=(const Vector2D &pOtherVector);
	Vector2D operator*=(const Vector2D &pOtherVector);
	Vector2D operator/=(const Vector2D &pOtherVector);
	bool	 operator==(const Vector2D &pOtherVector);
	bool	 operator!=(const Vector2D &pOtherVector);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D &pDisplayVector);
};

