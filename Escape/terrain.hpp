#pragma once
#include <glew.h>
#include <iostream>
#include <vec2.hpp>
#include <vector>
// model class
#include "model.hpp"
// loader class
#include "loader.hpp"
// math class
#include "math.hpp"

class Terrain
{
public:
	Terrain(int pGridX, int pGridZ, int pAmplitude, int pVertices, const char* pName, Loader* pLoader);
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

	glm::mat4 getModelMatrix();
	Model* getModel();
	void setModel(Model* pModel);

public:
	static const int TERRAIN_SIZE = 200;

private:
	int mWorldX;
	int mWorldZ;
	int mAmplitude;
	// Getters & Setters needed? Maybe static
	int mVertices;
	const char* mName;
	Model* mModel;

private:
	bool isPowerOfTwo(int pX);
	Model generateTerrain(Loader* loader);
	
};

