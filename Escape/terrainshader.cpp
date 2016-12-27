#include "terrainshader.hpp"



TerrainShader::TerrainShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{
	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	this->getAllUniformLocations();
	this->bindAllAttributes();
}

void TerrainShader::getAllUniformLocations()
{
	setModelMatrixLocation(glGetUniformLocation(this->getProgramID(), "model"));
	setProjectionMatrixLocation(glGetUniformLocation(this->getProgramID(), "projection"));
	setViewMatrixLocation(glGetUniformLocation(this->getProgramID(), "view"));
}

GLuint TerrainShader::getModelMatrixLocation() const
{
	return mModelMatrixLocation;
}

GLuint TerrainShader::getUniformLocation(const char* pUniformName)
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

GLuint TerrainShader::getViewMatrixLocation() const
{
	return mViewMatrixLocation;
}

GLuint TerrainShader::getProjectionMatrixLocation() const
{
	return mProjectionMatrixLocation;
}

void TerrainShader::setModelMatrixLocation(GLuint pModelMatrixLocation)
{
	mModelMatrixLocation = pModelMatrixLocation;
}

void TerrainShader::setViewMatrixLocation(GLuint pViewMatrixLocation)
{
	mViewMatrixLocation = pViewMatrixLocation;
}

void TerrainShader::setProjectionMatrixLocation(GLuint pProjectionMatrixLocation)
{
	mProjectionMatrixLocation = pProjectionMatrixLocation;
}

void TerrainShader::loadModelMatrix(glm::mat4 pMatrix)
{
	this->loadMatrix(this->getModelMatrixLocation(), pMatrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 pMatrix)
{
	this->loadMatrix(this->getProjectionMatrixLocation(), pMatrix);
}

void TerrainShader::loadViewMatrix(glm::mat4 pMatrix)
{
	this->loadMatrix(this->getViewMatrixLocation(), pMatrix);
}

TerrainShader::~TerrainShader()
{
}

void TerrainShader::bindAllAttributes()
{
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "normal");
	this->bindAttribute(2, "texCoord");
}
