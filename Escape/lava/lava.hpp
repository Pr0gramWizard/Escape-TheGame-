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

using namespace std;

class Lava
{
public:
	Lava(float pWorldX, float pWorldY, float pWorldZ, int pVertices, const char* pName, Loader* pLoader);
	~Lava();

	// Getter functions
	float getWorldX() const;
	float getWorldY() const;
	float getWorldZ() const;
	glm::vec3 getWorldPos() const;
	const char* getName();

	// Setter functions
	void setName(const char* pName);

	glm::mat4 getModelMatrix();
	Model* getModel();
	void setModel(Model* pModel);
	GLuint getBurningTexture();

public:
	static const int LAVA_SIZE;

private:
	float mWorldX;
	float mWorldY;
	float mWorldZ;
	// Getters & Setters needed? Maybe static
	int mVertices;
	float mGridSize;
	const char* mName;
	Model mModel;
	GLuint mPosVbo;
	GLuint mNormalVbo;

	GLuint mBurningTexture;

private:
	Model generateLava(Loader* loader);
	void loadTextures();
};

