#include "lake.hpp"

const int Lake::LAKE_SIZE = 20;

Lake::Lake(int pWorldX, int pWorldY, int pWorldZ, int pAmplitude, int pVertices, const char * pName, Loader * pLoader)
{
	mWorldX = pWorldX;
	mWorldY = pWorldY;
	mWorldZ = pWorldZ;
	this->setAmplitude(pAmplitude);
	mVertices = pVertices;
	this->setName(pName);

	this->initLake(pLoader);
	this->setModel(&this->generateLake(pLoader));
}

Lake::~Lake()
{
}

int Lake::getWorldX() const
{
	return mWorldX;
}

int Lake::getWorldY() const
{
	return mWorldY;
}

int Lake::getWorldZ() const
{
	return mWorldZ;
}

glm::vec3 Lake::getWorldPos() const
{
	return glm::vec3(mWorldX, mWorldY, mWorldZ);
}

const char * Lake::getName()
{
	return mName;
}

void Lake::setAmplitude(int pAmplitude)
{
	mAmplitude = pAmplitude;
}

void Lake::setName(const char * pName)
{
	mName = pName;
}

glm::mat4 Lake::getModelMatrix()
{
	return Math::getTransformationMatrix(glm::vec3(mWorldX, 0, mWorldZ), 0, 0, 0, 1);
}

Model * Lake::getModel()
{
	return &mModel;
}

void Lake::setModel(Model * pModel)
{
	mModel = *pModel;
}

GLfloat Lake::getHeight(int pVertexX, int pVertexZ)
{
	if (pVertexX < 0 || pVertexX >= mVertices || pVertexZ < 0 || pVertexZ >= mVertices)
	{
		return 0;
	}
	return mHeights[pVertexZ * mVertices + pVertexX];
}

void Lake::initLake(Loader * loader)
{
}

Model Lake::generateLake(Loader * loader)
{
	return Model();
}

void Lake::updateHeights()
{
}