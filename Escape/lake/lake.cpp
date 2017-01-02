#include "lake.hpp"

const int Lake::LAKE_SIZE = 20;

Lake::Lake(int pWorldX, int pWorldY, int pAmplitude, int pVertices, const char * pName, Loader * pLoader)
{
}

Lake::~Lake()
{
}

int Lake::getWorldX() const
{
	return 0;
}

int Lake::getWorldZ() const
{
	return 0;
}

glm::vec2 Lake::getWorldPos() const
{
	return glm::vec2();
}

const char * Lake::getName()
{
	return nullptr;
}

void Lake::setAmplitude(int pAmplitude)
{
}

void Lake::setName(const char * pName)
{
}

glm::mat4 Lake::getModelMatrix()
{
	return glm::mat4();
}

Model * Lake::getModel()
{
	return nullptr;
}

void Lake::setModel(Model * pModel)
{
}

void Lake::updateHeights()
{
}

Model Lake::generateLake(Loader * loader)
{
	return Model();
}

void Lake::initLake(Loader * loader)
{
}

GLfloat Lake::getHeight(int pVertexX, int pVertexZ)
{
	return GLfloat();
}
