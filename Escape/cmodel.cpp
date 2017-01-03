#include "cmodel.hpp"



cModel::cModel(std::vector<GLfloat> pVertices)
{
	glGenBuffers(1, &mVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayObject);
	glBufferData(GL_ARRAY_BUFFER, pVertices.size() * sizeof(pVertices[0]), pVertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

cModel::~cModel()
{
	this->unbind();
}

void cModel::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayObject);
}

void cModel::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void cModel::setVAO(GLuint pVAO)
{
	mVertexArrayObject = pVAO;
}

GLuint cModel::getVAO() const
{
	return mVertexArrayObject;
}


