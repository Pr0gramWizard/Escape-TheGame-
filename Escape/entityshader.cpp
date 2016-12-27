#include "entityshader.hpp"



EntityShader::EntityShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{
	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	this->getAllUniformLocations();
}

void EntityShader::getAllUniformLocations()
{
	setModelMatrixLocation(glGetUniformLocation(this->getProgramID(), "model"));
	setProjectionMatrixLocation(glGetUniformLocation(this->getProgramID(), "projection"));
	setViewMatrixLocation(glGetUniformLocation(this->getProgramID(), "view"));
}

GLuint EntityShader::getModelMatrixLocation() const
{
	return mModelMatrixLocation;
}

GLuint EntityShader::getViewMatrixLocation() const
{
	return mViewMatrixLocation;
}

GLuint EntityShader::getProjectionMatrixLocation() const
{
	return mProjectionMatrixLocation;
}

void EntityShader::setModelMatrixLocation(GLuint pModelMatrixLocation)
{
	mModelMatrixLocation = pModelMatrixLocation;
}

void EntityShader::setViewMatrixLocation(GLuint pViewMatrixLocation)
{
	mViewMatrixLocation = pViewMatrixLocation;
}

void EntityShader::setProjectionMatrixLocation(GLuint pProjectionMatrixLocation)
{
	mProjectionMatrixLocation = pProjectionMatrixLocation;
}

void EntityShader::loadModelMatrix(glm::mat4 pMatrix)
{
	this->loadMatrix(this->getModelMatrixLocation(), pMatrix);
}

void EntityShader::loadProjectionMatrix(glm::mat4 pMatrix)
{
	this->loadMatrix(this->getProjectionMatrixLocation(), pMatrix);
}

void EntityShader::loadViewMatrix(glm::mat4 pMatrix)
{
	this->loadMatrix(this->getViewMatrixLocation(), pMatrix);
}

EntityShader::~EntityShader()
{
}
