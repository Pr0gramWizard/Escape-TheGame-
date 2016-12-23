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

	Model loadDataToVao(float pPositions[], int pPositionSize, int pIndices[], int pIndicesSize, int pIndicesSizeElem0/*, float pNormals[], float pTexCoords[]*/);
	void cleanUp();

private:
	GLuint createVao();
	void unbindVao();
	void storeData(GLuint pAttributeLocation, float pData[], int pDataLength, int pLength);
	void deleteVaos();
	void deleteVbos();
	void bindIndices(int pIndices[], int pIndizesLength);

private:
	std::list<GLuint> mVaos;
	std::list<GLuint> mVbos;
};

