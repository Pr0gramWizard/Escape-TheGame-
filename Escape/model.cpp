#include "model.hpp"

Model::Model(int pVaoId, int pVertices, glm::vec3 pPosition)
{
	mVaoId = pVaoId;
	//Amount of vertices
	mVertices = pVertices;
	setPosition(pPosition);
}


Model::~Model()
{
}

int Model::getVaoId() {
	return mVaoId;
}

int Model::getVerticesCount() {
	return mVertices;
}

glm::mat4 Model::getModelMatrix() const
{
	glm::mat4 model;
	model = glm::translate(model, getPosition());
	return model;
}

glm::vec3 Model::getPosition() const
{
	return mPosition;
}

void Model::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}
