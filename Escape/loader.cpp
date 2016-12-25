#include "math.hpp"
#include "loader.hpp"
using namespace std;

Loader::Loader()
{
	
}

Loader::~Loader()
{
}
;
Model Loader::loadDataToVao(std::vector<float> pPositions, std::vector<float> pTexCoords, std::vector<float> pNormals, std::vector<int> pIndices, glm::vec3 pPostion)
{
	GLuint vaoId = createVao();
	bindIndices(pIndices);
	storeData(0, pPositions, 3);
	//storeData(1, pNormals, 3);
	//storeData(2, pTexCoords, 2);
	//storeData(3, pIndices, 3);
	unbindVao();
	return Model(vaoId, pIndices.size(),pPostion);
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

void Loader::bindIndices(std::vector<int> pIndices) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	mVbos.push_back(vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndices.size() * sizeof(int), &pIndices[0], GL_STATIC_DRAW);
}

void Loader::storeData(GLuint pAttributeLocation, std::vector<float> pData, int pSize)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	mVbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, pData.size() * sizeof(float),	&pData[0], GL_STATIC_DRAW);
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