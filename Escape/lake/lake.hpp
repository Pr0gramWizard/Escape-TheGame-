#pragma once

#include <glew.h>
#include <iostream>
#include <vec2.hpp>
#include <vector>
// model class
#include "../model.hpp"
// loader class
#include "../loader.hpp"
// math class
#include "../math.hpp"

class Lake
{
public:
	Lake(int pWorldX, int pWorldY, int pAmplitude, int pVertices, const char* pName, Loader* pLoader);
	~Lake();

	// Getter functions
	int getWorldX() const;
	int getWorldZ() const;
	glm::vec2 getWorldPos() const;
	const char* getName();

	// Setter functions
	void setAmplitude(int pAmplitude);
	void setName(const char* pName);

	glm::mat4 getModelMatrix();
	Model* getModel();
	void setModel(Model* pModel);

	void updateHeights();
public:
	static const int LAKE_SIZE;

private:
	int mWorldX;
	int mWorldZ;
	int mAmplitude;
	// Getters & Setters needed? Maybe static
	int mVertices;
	float mGridSize;
	const char* mName;
	Model mModel;
	std::vector<float> mHeights;
	std::vector<float> mVelocity;

private:
	Model generateLake(Loader* loader);
	void initLake(Loader* loader);
	GLfloat getHeight(int pVertexX, int pVertexZ);
};

