#include "model.hpp"

Model::Model()
{
	std::cout << "A new instance of the model class was started successfully!" << std::endl;
}


Model::~Model()
{
}

GLuint Model::getVAO() const{
	return mVAO;
}

GLuint Model::getVertexVBO() const {
	return mVertexVBO;
}

GLuint Model::getIndexVBO() const
{
	return mIndexVBO;
}

std::vector<float> Model::getVertices() const{
	return mVertices;
}

std::vector<unsigned int> Model::getIndices() const {
	return mIndices;
}

glm::mat4 Model::getModelMatrix() const
{
	return mModelMatrix;
}

const char * Model::getModelName() const
{
	return mModelName;
}

void Model::setVAO(GLuint pVAO)
{
	mVAO = pVAO;
}

void Model::setVertexVBO(GLuint pVBO)
{
	mVertexVBO = pVBO;
}

void Model::setIndexVBO(GLuint pVBO)
{
	mIndexVBO = pVBO;
}

void Model::setVertices(std::vector<float> pVertices)
{
	mVertices = pVertices;
}

void Model::setIndices(std::vector<unsigned int> pIndices)
{
	mIndices = pIndices;
}

void Model::setModelMatrix(glm::vec3 pTranslation, glm::vec3 pRotation, glm::vec3 pScaling)
{
	glm::mat4 Translation;
	Translation = glm::translate(Translation, pTranslation);

	glm::mat4 Rotation;
	// Rotation = glm::rotate(Rotation, 90.0f, pRotation);

	glm::mat4 Scaling;
	Scaling = glm::scale(Scaling, pScaling);

	mModelMatrix = Translation * Rotation * Scaling;
}

glm::vec3 Model::getPosition() const
{
	return mPosition;
}

void Model::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

void Model::setModelName(const char * pModelName)
{
	mModelName = pModelName;
}
