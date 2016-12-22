#include "loader.hpp"
using namespace std;

Loader::Loader()
{
	
}

Loader::~Loader()
{
}

Model Loader::loadDataToVao(float pPositions[]/*, float pNormals[], float pTexCoords[], float pIndices[]*/)
{
	GLuint vaoId = createVao();
	storeData(0, pPositions, 3);
	//storeData(1, pNormals, 3);
	//storeData(2, pTexCoords, 2);
	//storeData(3, pIndices, 3);
	unbindVao();
	return Model(vaoId, (sizeof(pPositions) / sizeof(pPositions[0]))/3.0 /*sizeof(pIndices)/sizeof(pIndices[0])*/);
}

GLuint Loader::createVao()
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	mVaos.push_back(vao);
	return vao;
}

void Loader::unbindVao()
{
	glBindVertexArray(0);
}

void Loader::storeData(GLuint pAttributeLocation, float pData[], int pLength)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pData) / sizeof(pData[0]) * sizeof(float), pData, GL_STATIC_DRAW);
	glVertexAttribPointer(pAttributeLocation, pLength, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	mVbos.push_back(vbo);
}

void Loader::deleteVaos() 
{
	for (GLuint vao : mVaos)
	{
		glDeleteVertexArrays(1, &vao);
	}
}

void Loader::deleteVbos() 
{
	for (GLuint vbo : mVbos) 
	{
		glDeleteBuffers(1, &vbo);
	}
}

void Loader::cleanUp() {
	unbindVao();
	deleteVaos();
	deleteVbos();
}