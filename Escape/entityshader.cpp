#include "entityshader.hpp"



EntityShader::EntityShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{
	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	this->getAllUniformLocations();
	this->bindAllAttributes();
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
void EntityShader::Test()
{
	std::cout << this->getProgramID() << std::endl;
}
GLuint EntityShader::getUniformLocation(const char* pUniformName)
{
	GLuint Location = glGetUniformLocation(this->getProgramID(), pUniformName);

	if (Location == GL_INVALID_INDEX)
	{
		std::clog << "There was an error finding: " << pUniformName << std::endl;
		return 0;
	}
	else
	{
		return Location;
	}
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

void EntityShader::bindAllAttributes()
{
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "normal");
	this->bindAttribute(2, "texCoord");
}
