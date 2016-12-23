#include "math.hpp"
#include "loader.hpp"
using namespace std;

Loader::Loader()
{
	
}

Loader::~Loader()
{
}

Model Loader::loadDataToVao(float pPositions[], int pPositionSize, int pIndices[], int pIndicesSize, int pIndicesSizeElem0/*, float pNormals[], float pTexCoords[], */)
{
	GLuint vaoId = createVao();
	bindIndices(pIndices, pIndicesSize);
	storeData(0, pPositions, pPositionSize, 3);
	//storeData(1, pNormals, 3);
	//storeData(2, pTexCoords, 2);
	//storeData(3, pIndices, 3);
	unbindVao();
	return Model(vaoId, (pIndicesSize / pIndicesSizeElem0));
}

GLuint Loader::createVao()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	mVaos.push_back(vao);
	glBindVertexArray(vao);
	return vao;
}

void Loader::unbindVao()
{
	glBindVertexArray(0);
}

void Loader::bindIndices(int pIndices[], int pIndizesLength) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	mVbos.push_back(vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndizesLength * sizeof(int), pIndices, GL_STATIC_DRAW);
}

void Loader::storeData(GLuint pAttributeLocation, float pData[], int pDataLength, int pSize)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	mVbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, pDataLength, pData, GL_STATIC_DRAW);
	glVertexAttribPointer(pAttributeLocation, pSize, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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