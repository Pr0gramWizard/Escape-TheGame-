#pragma once
#include <glew.h>
#include <iostream>
#include <vec3.hpp>
#include <vec2.hpp>


class Terrain
{
public:
	Terrain(int pWorldX, int pWorldY, int pHeight, int pWidht, int pDepth, glm::vec3 pStartPoint, int pVertices, const char* pName);
	GLfloat* getVertices(int pTiles);
	~Terrain();

	// Getter functions
	int getWidth() const;
	int getHeight() const;
	int getDepth() const;
	int getWorldX() const;
	int getWorldY() const;
	glm::vec2 getWorldPos() const;
	glm::vec3 getStartPoint() const;
	const char* getName();

	// Setter functions
	void setWidth(int pWidth);
	void setHeight(int pHeight);
	void setDepth(int pDepth);
	void setStartPoint(glm::vec3 pStartPoint);
	void setName(const char* pName);

private:
	int mWorldX;
	int mWorldY;
	int mWidth;
	int mHeight;
	int mDepth;
	glm::vec3 mStartPoint;
	// Getters & Setters needed? Maybe static
	int mVertices;
	const char* mName;

private:
	bool isPowerOfTwo(int pX);
	
};

