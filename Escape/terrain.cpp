#include "terrain.hpp"



Terrain::Terrain()
{
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
