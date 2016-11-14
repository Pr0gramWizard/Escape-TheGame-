#include "cube.hpp"



Cube::Cube()
{
	setVertices(0);
	setRotation(0);

	std::clog << "Cube instance was successfully created!" << std::endl;
}

Cube::Cube(GLfloat pVertices[24], GLfloat pSides[6][4])
{
	setVertices(pVertices);
	setSides(pSides);

	std::clog << "Cube instance was successfully created!" << std::endl;
}

void Cube::properties()
{
	
}


Cube::~Cube()
{
}

void Cube::setVertices(GLfloat pVertices[24])
{
	for (int i = 0; i < 24; ++i)
	{
			mVertices[i] = pVertices[i];
	}
}

void Cube::setVerticesVector3D(Vector3D pVertices, int pPosition)
{
	mVertices[0 + pPosition] = pVertices.x;
	mVertices[1 + pPosition] = pVertices.y;
	mVertices[2 + pPosition] = pVertices.z;
}

void Cube::setSides(GLfloat pSides[6][4])
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
			mSides[i][j] = pSides[i][j];
	}
}

void Cube::setSide(GLfloat pSide[4], int pPosition)
{
	mSides[pPosition][0] = pSide[0];
	mSides[pPosition][1] = pSide[1];
	mSides[pPosition][2] = pSide[2];
	mSides[pPosition][2] = pSide[3];
}

void Cube::setRotation(GLfloat pRotation)
{
	mRotation = pRotation;
}

void Cube::setColor(GLfloat pColor[3])
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


GLfloat Cube::getVertices(int i)
{
	return mVertices[i];
}

Vector3D Cube::getVerticesVector3D(int i)
{
	return Vector3D(mVertices[0 + i], mVertices[1 +i], mVertices[2 + i]);
}

GLfloat Cube::getSides(int i, int j)
{
	return mSides[i][j];
}

Vector4D Cube::getSidesVector4D(int i)
{
	return Vector4D(mSides[i][0], mSides[i][1], mSides[i][2], mSides[i][3]);
}

Vector3D Cube::getColor()
{
	return mColor;
}

GLfloat Cube::getRotation() const
{
	return mRotation;
}
