#include "vector3D.hpp"

Vector3D::Vector3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3D::Vector3D(const float &pX, const float &pY, const float &pZ)
{
	this->x = pX;
	this->y = pY;
	this->z = pZ;
}

Vector3D& Vector3D::operator+(const Vector3D & pOtherVector)
{
	this->x = this->x + pOtherVector.x;
	this->y = this->y + pOtherVector.y;
	this->z = this->z + pOtherVector.z;

	return *this;
}

Vector3D& Vector3D::operator-(const Vector3D & pOtherVector)
{
	this->x = this->x - pOtherVector.x;
	this->y = this->y - pOtherVector.y;
	this->z = this->z - pOtherVector.z;

	return *this;
}

Vector3D& Vector3D::operator*(const Vector3D & pOtherVector)
{
	this->x = this->x * pOtherVector.x;
	this->y = this->y * pOtherVector.y;
	this->z = this->z * pOtherVector.z;

	return *this;
}

Vector3D& Vector3D::operator/(const Vector3D & pOtherVector)
{
	this->x = this->x / pOtherVector.x;
	this->y = this->y / pOtherVector.y;
	this->z = this->z / pOtherVector.z;

	return *this;
}



Vector3D& Vector3D::operator+=(const Vector3D & pOtherVector)
{
	this->x = this->x + pOtherVector.x;
	this->y = this->y + pOtherVector.y;
	this->z = this->z + pOtherVector.z;

	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D & pOtherVector)
{
	this->x = this->x - pOtherVector.x;
	this->y = this->y - pOtherVector.y;
	this->z = this->z - pOtherVector.z;

	return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D & pOtherVector)
{
	this->x = this->x * pOtherVector.x;
	this->y = this->y * pOtherVector.y;
	this->z = this->z * pOtherVector.z;

	return *this;
}

Vector3D& Vector3D::operator/=(const Vector3D & pOtherVector)
{
	this->x = this->x / pOtherVector.x;
	this->y = this->y / pOtherVector.y;
	this->z = this->z / pOtherVector.z;

	return *this;
}

bool Vector3D::operator==(const Vector3D & pOtherVector)
{
	if (this->x == pOtherVector.x && this->y == pOtherVector.y && this->z == pOtherVector.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vector3D::operator!=(const Vector3D & pOtherVector)
{
	if (*this == pOtherVector)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Vector3D  Vector3D::normalize()
{
	Vector3D Result(1.0f,1.0f,1.0f);

	float x = this->x;
	float y = this->y;
	float z = this->z;

	float factor = 1/sqrt((x*x) + (y*y) + (z*z));

	Result.x = this->x;
	Result.y = this->y;
	Result.z = this->z;

	Result.x = Result.x * factor;
	Result.y = Result.y * factor;
	Result.z = Result.z * factor;

	return Result;
}

std::ostream& operator<<(std::ostream& stream, const Vector3D &pDisplayVector)
{
	stream << "3D Vector: (" << pDisplayVector.x << "," << pDisplayVector.y << "," << pDisplayVector.z << ")";
	return stream;
}
