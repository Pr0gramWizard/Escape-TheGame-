#pragma once

#include <iostream>

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D();
	Vector3D(const float &pX, const float &pY, const float &pZ);

	Vector3D& operator+(const Vector3D &pOtherVector);
	Vector3D& operator-(const Vector3D &pOtherVector);
	Vector3D& operator-();
	Vector3D& operator*(const Vector3D &pOtherVector);
	Vector3D& operator*(const float &pFactor);
	Vector3D& operator/(const Vector3D &pOtherVector);
	Vector3D& operator+=(const Vector3D &pOtherVector);
	Vector3D& operator-=(const Vector3D &pOtherVector);
	Vector3D& operator*=(const Vector3D &pOtherVector);
	Vector3D& operator/=(const Vector3D &pOtherVector);
	bool	 operator==(const Vector3D &pOtherVector);
	bool	 operator!=(const Vector3D &pOtherVector);

	// Functions
	Vector3D normalize();
	Vector3D crossproduct(const Vector3D &pOtherVector);
	float dotproduct(const Vector3D &pOtherVector);

	friend std::ostream& operator<<(std::ostream& stream, const Vector3D &pDisplayVector);
};

