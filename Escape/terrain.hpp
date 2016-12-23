#pragma once
#include <glew.h>
#include <iostream>
#include <vec3.hpp>
#include <vec2.hpp>


class Terrain
{
public:
	Terrain(int pWorldX, int pWorldY, int pAmplitude, int pVertices, const char* pName);
	GLfloat* getVertices(int pTiles);
	~Terrain();

	// Getter functions
	int getWorldX() const;
	int getWorldZ() const;
	glm::vec2 getWorldPos() const;
	const char* getName();

	// Setter functions
	void setAmplitude(int pAmplitude);
	void setVertices(int pVertices);
	void setName(const char* pName);

public:
	static const int TERRAIN_SIZE = 200;

private:
	int mWorldX;
	int mWorldZ;
	int mAmplitude;
	// Getters & Setters needed? Maybe static
	int mVertices;
	const char* mName;

private:
	bool isPowerOfTwo(int pX);
	
};

