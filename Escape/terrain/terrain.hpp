#pragma once
#include <glew.h>
#include <iostream>
#include <vec2.hpp>
#include <vector>
// model class
#include "../model/model.hpp"
// loader class
#include "../loader/loader.hpp"
// math class
#include "../math/math.hpp"



class Terrain
{
public:
	Terrain(int pGridX, int pGridZ, int pAmplitude, const char* pName, Loader* pLoader);
	~Terrain();

	void loadGrasTexture();
	void loadStoneTexture();

	// Getter functions
	int getWorldX() const;
	int getWorldZ() const;
	glm::vec2 getWorldPos() const;
	const char* getName();

	// Setter functions
	void setAmplitude(int pAmplitude);
	void setVertices(int pVertices);
	void setName(const char* pName);


	GLuint getGrasTexture();
	GLuint getStoneTexture();
	glm::mat4 getModelMatrix();
	Model* getModel();
	void setModel(Model* pModel);
	GLfloat getHeight(float x, float z);

	
public:
	static const int TERRAIN_SIZE;

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
	GLuint mGrassTex;
	GLuint mStoneTex;

private:
	bool isPowerOfTwo(int pX);
	Model generateTerrain(Loader* loader);
	void generateHeights(Loader* loader);
	glm::vec3 computeNormalAt(int x, int z);
	GLfloat getVertexHeight(int pVertexX, int pVertexZ);

};

