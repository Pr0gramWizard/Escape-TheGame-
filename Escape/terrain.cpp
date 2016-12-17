#include "terrain.hpp"



Terrain::Terrain(int pHeight, int pDepth ,int pWidth, glm::vec3 pStartPoint)
{
	// X 
	setHeight(pHeight);
	// Y
	setDepth(pDepth);
	// Z
	setWidth(pWidth);
	// Start Point
	setStartPoint(pStartPoint);
	std::cout << "Terrain class loaded!" << std::endl;
}


Terrain::~Terrain()
{
}

int Terrain::getWidth() const
{
	return mWidth;
}

int Terrain::getHeight() const
{
	return mHeight;
}

int Terrain::getDepth() const
{
	return mDepth;
}

glm::vec3 Terrain::getStartPoint() const
{
	return mStartPoint;
}

const char * Terrain::getName() const
{
	return mName;
}

void Terrain::setWidth(int pWidth)
{
	mWidth = pWidth;
}

void Terrain::setHeight(int pHeight)
{
	mHeight = pHeight;
}

void Terrain::setDepth(int pDepth)
{
	mDepth = pDepth;
}

void Terrain::setStartPoint(glm::vec3 pStartPoint)
{
	mStartPoint = pStartPoint;
}

void Terrain::setName(const char * pName)
{
	mName = pName;
}
