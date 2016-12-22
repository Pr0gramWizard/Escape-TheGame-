#include "terrain.hpp"



Terrain::Terrain(int pWorldX, int pWorldY, int pHeight, int pDepth ,int pWidth, glm::vec3 pStartPoint, int pVertices, const char* pName)
{
	// Worldspace coordinates
	mWorldX = pWorldX;
	mWorldY = pWorldY;
	// X 
	setHeight(pHeight);
	// Y
	setDepth(pDepth);
	// Z
	setWidth(pWidth);
	// Start Point
	setStartPoint(pStartPoint);
	// Amount of vertices along one side
	mVertices = pVertices;
	// Name
	setName(pName);

	std::cout << "Terrainloader was started successfully!" << std::endl;

}

GLfloat* Terrain::getVertices(int pTiles)
{
	if(!isPowerOfTwo(pTiles))
	{
		std::cout << "There was an error! The number of tiles is not a power of 2!" << std::endl;
	}

	GLfloat Test[]  = { 1.0f,2.0f };
	return Test;
}


Terrain::~Terrain()
{
	std::cout << "Terrainloader was stopped successfully!" << std::endl;
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

int Terrain::getWorldX() const
{
	return mWorldX;
}

int Terrain::getWorldY() const
{
	return mWorldY;
}

glm::vec2 Terrain::getWorldPos() const
{
	return glm::vec2(mWorldX, mWorldY);
}

glm::vec3 Terrain::getStartPoint() const
{
	return mStartPoint;
}

const char * Terrain::getName()
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

bool Terrain::isPowerOfTwo(int pX)
{
	return !(pX == 0) && !(pX & (pX - 1));
}
