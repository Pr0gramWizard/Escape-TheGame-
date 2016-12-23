#pragma once
// GLEW
#define GLEW_STATIC
#include <glew.h>
// list
#include <list>
#include <vector>
// Model class
#include "model.hpp"

class Loader
{
public:
	Loader();
	~Loader();

	Model loadDataToVao(std::vector<float> pPositions, std::vector<float> pTexCoords, std::vector<float> pNormals, std::vector<int> pIndices);
	void cleanUp();

private:
	GLuint createVao();
	void unbindVao();
	void storeData(GLuint pAttributeLocation, std::vector<float> pData, int pLength);
	void deleteVaos();
	void deleteVbos();
	void bindIndices(std::vector<int> pIndices);

private:
	std::list<GLuint> mVaos;
	std::list<GLuint> mVbos;
};

