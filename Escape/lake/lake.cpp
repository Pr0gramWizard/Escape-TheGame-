#include "lake.hpp"

const int Lake::LAKE_SIZE = 64;
const GLfloat Lake::LAKE_COEFFICIENT = 7.0f;

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
	mPosVbo = pLoader->getLastVbos().y;
	mNormalVbo = pLoader->getLastVbos().z;
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

GLfloat Lake::getVertexHeight(int pVertexX, int pVertexZ)
{
	if (pVertexX < 0)
	{
		pVertexX = 0;
	}
	else if (pVertexX >= mVertices)
	{
		pVertexX = mVertices - 1;
	}
	
	if (pVertexZ < 0) 
	{
		pVertexZ = 0;
	}
	else if (pVertexZ >= mVertices)
	{
		pVertexZ = mVertices - 1;
	}
	
	return mHeights[pVertexZ * mVertices + pVertexX];
}

void Lake::initLake(Loader * loader)
{
	mVelocity = vector<float>(mVertices * mVertices, 0.0f);
	mHeights = vector<float>(mVertices * mVertices, this->getWorldY());
	mVaryingPositions = vector<float>(mVertices * mVertices * 3, 0.0f);
	mVaryingNormals = vector<float>(mVertices * mVertices * 3, 0.0f);

	int half = (int)(mVertices / 2.0f);

	mVelocity[half * mVertices + half] = -5;
	mVelocity[half * mVertices + half - 1] = -2.5f;
	mVelocity[half * mVertices + half + 1] = -2.5f;
	mVelocity[(half + 1) * mVertices + half] = -2.5f;
	mVelocity[(half - 1) * mVertices + half] = -2.5f;

	// generates random heights between -mAmplitude and +mAmplitude
	/*for (int i = 0; i < mHeights.size(); ++i)
	{
		mHeights[i] = ((float)rand() / (float)(RAND_MAX)) * (2 * mAmplitude) - mAmplitude;
	}*/
}

Model Lake::generateLake(Loader * loader)
{
	// set grid size
	mGridSize = (float)Lake::LAKE_SIZE / (mVertices - 1);
	int count = mVertices * mVertices;
	std::vector<float> textureCoords(count * 2);
	std::vector<int> indices(6 * (mVertices - 1)*(mVertices - 1));
	int vertexPointer = 0;
	for (int z = 0;z<mVertices;z++) {
		for (int x = 0;x<mVertices;x++) {
			mVaryingPositions[vertexPointer * 3] = (float)x / ((float)mVertices - 1) * Lake::LAKE_SIZE;
			mVaryingPositions[vertexPointer * 3 + 1] = this->getVertexHeight(x, z);
			mVaryingPositions[vertexPointer * 3 + 2] = (float)z / ((float)mVertices - 1) * Lake::LAKE_SIZE;
			mVaryingNormals[vertexPointer * 3] = 0;
			mVaryingNormals[vertexPointer * 3 + 1] = 1;
			mVaryingNormals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)x / ((float)mVertices - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)z / ((float)mVertices - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0;gz<mVertices - 1;gz++) {
		for (int gx = 0;gx<mVertices - 1;gx++) {
			int topLeft = (gz*mVertices) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*mVertices) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	return loader->loadDataToVao(mVaryingPositions, textureCoords, mVaryingNormals, indices);
}

void Lake::updateVelocities()
{
	for (int z = 1;z < mVertices - 1;z++) {
		for (int x = 1;x < mVertices - 1;x++) {
			mVelocity[z * mVertices + x] += LAKE_COEFFICIENT*((this->getVertexHeight(x - 1, z) + this->getVertexHeight(x + 1, z) + this->getVertexHeight(x, z - 1) + this->getVertexHeight(x, z + 1)) / 4 - this->getVertexHeight(x, z));
			mVelocity[z * mVertices + x] *= 0.99f;
		}
	}
}

void Lake::updateNormals()
{
	int vertexPointer = 0;
	// update the normals
	float hL, hR, hD, hU;
	for (int z = 1;z < mVertices - 1;z++) {
		for (int x = 1;x < mVertices - 1;x++) {

			hL = mHeights[z * mVertices + (x - 1)]; // this->getVertexHeight(x - 1, z);
			hR = mHeights[z * mVertices + (x + 1)]; //this->getVertexHeight(x + 1, z);
			hD = mHeights[(z - 1) * mVertices + x]; //this->getVertexHeight(x, z - 1);
			hU = mHeights[(z + 1) * mVertices + x]; //this->getVertexHeight(x, z + 1);

			// deduce terrain normal
			glm::vec3 normal = glm::normalize(glm::vec3(hL - hR, 2.0f, hD - hU));
			mVaryingNormals[vertexPointer * 3] = normal.x;
			mVaryingNormals[vertexPointer * 3 + 1] = normal.y;
			mVaryingNormals[vertexPointer * 3 + 2] = normal.z;
			vertexPointer++;
		}
	}
}

void Lake::updatePositionVBO()
{
	// update position vbo
	glBindBuffer(GL_ARRAY_BUFFER, mPosVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, mVaryingPositions.size() * sizeof(float), &mVaryingPositions[0]);
	// update normal vbo
	glBindBuffer(GL_ARRAY_BUFFER, mNormalVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, mVaryingNormals.size() * sizeof(float), &mVaryingNormals[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Lake::updateHeights(GLfloat pDeltaTime)
{
	this->updateVelocities();
	int vertexPointer = 0;
	// update the heights
	for (int z = 1;z < mVertices -1;z++) {
		for (int x = 1;x < mVertices - 1;x++) {
			mHeights[z * mVertices + x] += mVelocity[z * mVertices + x] * pDeltaTime;
			// update vertices
			mVaryingPositions[vertexPointer * 3 + 1] = mHeights[z * mVertices + x];
			vertexPointer++;
		}
	}
	this->updateNormals();
	this->updatePositionVBO();
}