#include "cube.hpp"



Cube::Cube()
{
	setVertices(0);
	setRotation(0);

	std::clog << "Cube instance was successfully created!" << std::endl;
}

Cube::Cube(GLfloat pVertices[8][3], GLfloat pSides[6][4])
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

void Cube::setVertices(GLfloat pVertices[8][3])
{
	for (int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 3; ++j)
			mVertices[i][j] = pVertices[i][j];
	}
}

void Cube::setVerticesVector3D(Vector3D pVertices, int pPosition)
{
	mVertices[pPosition][0] = pVertices.x;
	mVertices[pPosition][1] = pVertices.y;
	mVertices[pPosition][2] = pVertices.z;
}

void Cube::setSides(GLfloat pVertices[6][4])
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
			mSides[i][j] = pVertices[i][j];
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


GLfloat Cube::getVertices(int i, int j)
{
	return mVertices[i][j];
}

Vector3D Cube::getVerticesVector3D(int i)
{
	return Vector3D(mVertices[i][0], mVertices[i][1], mVertices[i][2]);
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
