#include "loaderX.hpp"



LoaderX::LoaderX()
{
	// Log Message
	std::cout << "LoaderX was started successfully!" << std::endl;
}

Model* LoaderX::createModel(Object pObject)
{
	Model* cModel = new Model();

	cModel->setPosition(pObject.getPosition());
	cModel->setVertices(pObject.getVertices());
	cModel->setIndices(pObject.getIndices());
	cModel->setVAO(createVAO());
	cModel->setVertexVBO(createVertexVBO(0,pObject.getVertices()));
	cModel->setIndexVBO(createIndexVBO(pObject.getIndices()));
	unbindVAO();
	return cModel;
}

GLuint LoaderX::createVAO()
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	return VAO;
}

GLuint LoaderX::createVertexVBO(int pAttributeNumber, std::vector<float> pVertices)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	
	glBufferData(GL_ARRAY_BUFFER, pVertices.size() * sizeof(float),&pVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(pAttributeNumber, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return VBO;
}

GLuint LoaderX::createIndexVBO(std::vector<unsigned int> pIndices)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndices.size() * sizeof(int), &pIndices[0], GL_STATIC_DRAW);
	return VBO;
}

void LoaderX::unbindVAO()
{
	glBindVertexArray(0);
}

LoaderX::~LoaderX()
{
}
