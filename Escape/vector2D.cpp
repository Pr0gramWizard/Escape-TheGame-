#include "vector2D.hpp"



Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(const float & pX, const float & pY)
{
	this->x = pX;
	this->y = pY;
}

Vector2D Vector2D::operator+(const Vector2D & pOtherVector)
{
	this->x = this->x + pOtherVector.x;
	this->y = this->y + pOtherVector.y;

	return *this;
}

Vector2D Vector2D::operator-(const Vector2D & pOtherVector)
{
	this->x = this->x - pOtherVector.x;
	this->y = this->y - pOtherVector.y;

	return *this;
}

Vector2D Vector2D::operator*(const Vector2D & pOtherVector)
{
	this->x = this->x * pOtherVector.x;
	this->y = this->y * pOtherVector.y;

	return *this;
}

Vector2D Vector2D::operator/(const Vector2D & pOtherVector)
{
	this->x = this->x / pOtherVector.x;
	this->y = this->y / pOtherVector.y;

	return *this;
}

Vector2D Vector2D::operator=(const Vector2D & pOtherVector)
{
	this->x = pOtherVector.x;
	this->y = pOtherVector.y;

	return *this;
}

Vector2D Vector2D::operator+=(const Vector2D & pOtherVector)
{
	this->x = this->x + pOtherVector.x;
	this->y = this->y + pOtherVector.y;

	return *this;
}

Vector2D Vector2D::operator-=(const Vector2D & pOtherVector)
{
	this->x = this->x - pOtherVector.x;
	this->y = this->y - pOtherVector.y;

	return *this;
}

Vector2D Vector2D::operator*=(const Vector2D & pOtherVector)
{
	this->x = this->x * pOtherVector.x;
	this->y = this->y * pOtherVector.y;

	return *this;
}

Vector2D Vector2D::operator/=(const Vector2D & pOtherVector)
{
	this->x = this->x / pOtherVector.x;
	this->y = this->y / pOtherVector.y;

	return *this;
}

bool Vector2D::operator==(const Vector2D & pOtherVector)
{
	if (this->x == pOtherVector.x && this->y == pOtherVector.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vector2D::operator!=(const Vector2D & pOtherVector)
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

std::ostream& operator<<(std::ostream& stream, const Vector2D &pDisplayVector)
{
	stream << "2D Vector: (" << pDisplayVector.x << "," << pDisplayVector.y << ")";
	return stream;
}