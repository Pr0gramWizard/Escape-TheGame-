#pragma once

#include <iostream>


struct Vector4D
{
	float x;
	float y;
	float z;
	float w;

	Vector4D();
	Vector4D(const float &pX, const float &pY, const float &pZ, const float &pW);

	Vector4D& operator+(const Vector4D &pOtherVector);
	Vector4D& operator-(const Vector4D &pOtherVector);
	Vector4D& operator*(const Vector4D &pOtherVector);
	Vector4D& operator/(const Vector4D &pOtherVector);
	Vector4D& operator+=(const Vector4D &pOtherVector);
	Vector4D& operator-=(const Vector4D &pOtherVector);
	Vector4D& operator*=(const Vector4D &pOtherVector);
	Vector4D& operator/=(const Vector4D &pOtherVector);
	bool	 operator==(const Vector4D &pOtherVector);
	bool	 operator!=(const Vector4D &pOtherVector);

	friend std::ostream& operator<<(std::ostream& stream, const Vector4D &pDisplayVector);

	
};

