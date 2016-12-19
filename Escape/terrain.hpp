#pragma once
#include <glew.h>
#include <iostream>
#include <vec3.hpp>


class Terrain
{
public:
	Terrain(int pHeight, int pWidht, int pDepth, glm::vec3 pStartPoint, const char* pName);
	GLfloat* getVertices(int pTiles);
	~Terrain();

	// Getter functions
	int getWidth() const;
	int getHeight() const;
	int getDepth() const;
	glm::vec3 getStartPoint() const;
	const char* getName();

	// Setter functions
	void setWidth(int pWidth);
	void setHeight(int pHeight);
	void setDepth(int pDepth);
	void setStartPoint(glm::vec3 pStartPoint);
	void setName(const char* pName);

private:
	int mWidth;
	int mHeight;
	int mDepth;
	glm::vec3 mStartPoint;
	const char* mName;

private:
	bool isPowerOfTwo(int pX);
	
};

