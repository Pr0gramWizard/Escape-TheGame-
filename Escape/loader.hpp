#pragma once
// GLEW
#define GLEW_STATIC
#include <glew.h>
// list
#include <list>
// Model class
#include "model.hpp"

class Loader
{
public:
	Loader();
	~Loader();

	Model loadDataToVao(float pPositions[]/*, float pNormals[], float pTexCoords[], float pIndices[]*/);
	void cleanUp();

private:
	GLuint createVao();
	void unbindVao();
	void storeData(GLuint pAttributeLocation, float pData[], int pLength);
	void deleteVaos();
	void deleteVbos();

private:
	std::list<GLuint> mVaos;
	std::list<GLuint> mVbos;
};

