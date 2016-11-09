#include "vector4D.hpp"

Vector4D::Vector4D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Vector4D::Vector4D(const float &pX, const float &pY, const float &pZ, const float &pW)
{
	this->x = pX;
	this->y = pY;
	this->z = pZ;
	this->w = pW;
}

Vector4D& Vector4D::operator+(const Vector4D & pOtherVector)
{
	this->x = this->x + pOtherVector.x;
	this->y = this->y + pOtherVector.y;
	this->z = this->z + pOtherVector.z;
	this->w = this->w + pOtherVector.w;

	return *this;
}

Vector4D& Vector4D::operator-(const Vector4D & pOtherVector)
{
	this->x = this->x - pOtherVector.x;
	this->y = this->y - pOtherVector.y;
	this->z = this->z - pOtherVector.z;
	this->w = this->w - pOtherVector.w;

	return *this;
}

Vector4D& Vector4D::operator*(const Vector4D & pOtherVector)
{
	this->x = this->x * pOtherVector.x;
	this->y = this->y * pOtherVector.y;
	this->z = this->z * pOtherVector.z;
	this->w = this->w * pOtherVector.w;

	return *this;
}

Vector4D& Vector4D::operator/(const Vector4D & pOtherVector)
{
	this->x = this->x / pOtherVector.x;
	this->y = this->y / pOtherVector.y;
	this->z = this->z / pOtherVector.z;
	this->w = this->w / pOtherVector.w;

	return *this;
}



Vector4D& Vector4D::operator+=(const Vector4D & pOtherVector)
{
	this->x = this->x + pOtherVector.x;
	this->y = this->y + pOtherVector.y;
	this->z = this->z + pOtherVector.z;
	this->w = this->w + pOtherVector.w;

	return *this;
}

Vector4D& Vector4D::operator-=(const Vector4D & pOtherVector)
{
	this->x = this->x - pOtherVector.x;
	this->y = this->y - pOtherVector.y;
	this->z = this->z - pOtherVector.z;
	this->w = this->w - pOtherVector.w;


	return *this;
}

Vector4D& Vector4D::operator*=(const Vector4D & pOtherVector)
{
	this->x = this->x * pOtherVector.x;
	this->y = this->y * pOtherVector.y;
	this->z = this->z * pOtherVector.z;
	this->w = this->w * pOtherVector.w;

	return *this;
}

Vector4D& Vector4D::operator/=(const Vector4D & pOtherVector)
{
	this->x = this->x / pOtherVector.x;
	this->y = this->y / pOtherVector.y;
	this->z = this->z / pOtherVector.z;
	this->w = this->w / pOtherVector.w;

	return *this;
}

bool Vector4D::operator==(const Vector4D & pOtherVector)
{
	if (this->x == pOtherVector.x && this->y == pOtherVector.y && this->z == pOtherVector.z && this->w == pOtherVector.w)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vector4D::operator!=(const Vector4D & pOtherVector)
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

std::ostream& operator<<(std::ostream& stream, const Vector4D &pDisplayVector)
{
	stream << "4D Vector: (" << pDisplayVector.x << "," << pDisplayVector.y << "," << pDisplayVector.z << "," << pDisplayVector.w << ")";
	return stream;
}
