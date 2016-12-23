#include "terrain.hpp"



Terrain::Terrain(int pWorldX, int pWorldZ, int pAmplitude, int pVertices, const char* pName)
{
	// Worldspace coordinates
	mWorldX = pWorldX;
	mWorldZ = pWorldZ;
	
	// Set height amplitude for terrain
	setAmplitude(pAmplitude);

	// Set amount of vertices along a side of the terrain
	setVertices(pVertices);

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

int Terrain::getWorldX() const
{
	return mWorldX;
}

int Terrain::getWorldZ() const
{
	return mWorldZ;
}

glm::vec2 Terrain::getWorldPos() const
{
	return glm::vec2(mWorldX, mWorldZ);
}

const char * Terrain::getName()
{
	return mName;
}

void Terrain::setAmplitude(int pAmplitude)
{
	mAmplitude = pAmplitude;
}

void Terrain::setVertices(int pVertices)
{
	if (!isPowerOfTwo(pVertices))
	{
		mVertices = 128;
	}
	else
	{
		mVertices = pVertices;
	}
}

void Terrain::setName(const char * pName)
{
	mName = pName;
}

bool Terrain::isPowerOfTwo(int pX)
{
	return !(pX == 0) && !(pX & (pX - 1));
}
