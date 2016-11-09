#include "cube.hpp"



Cube::Cube()
{
	setVertices(0);
	setRotation(0);

	std::clog << "Cube instance was successfully created!" << std::endl;
}

Cube::Cube(float pVertices[108], float pRotation, Vector3D pColor)
{
	setVertices(pVertices);
	setRotation(pRotation);
	setColor(pColor);

	std::clog << "Cube instance was successfully created!" << std::endl;
}

void Cube::properties()
{
	
}


Cube::~Cube()
{
}

void Cube::setVertices(float pVertices[108])
{
	for (int i = 0; i < 108; i++)
	{
		mVertices[i] = pVertices[i];
	}
}

void Cube::setRotation(float pRotation)
{
	mRotation = pRotation;
}

void Cube::setColor(float pColor[3])
{
	mColor.x = pColor[0];
	mColor.y = pColor[1];
	mColor.z = pColor[2];
}

void Cube::setColor(Vector3D pColor)
{
	mColor.x = pColor.x;
	mColor.y = pColor.y;
	mColor.z = pColor.z;
}


float Cube::getVertices(int i)
{
	return mVertices[i];
}

Vector3D Cube::getColor()
{
	return mColor;
}

float Cube::getRotation() const
{
	return mRotation;
}
