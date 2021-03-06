#include "lava.hpp"

const int Lava::LAVA_SIZE = 38;

Lava::Lava(float pWorldX, float pWorldY, float pWorldZ, int pVertices, const char * pName, Loader * pLoader)
{
	mWorldX = pWorldX;
	mWorldY = pWorldY;
	mWorldZ = pWorldZ;
	mVertices = pVertices;
	this->setName(pName);

	this->setModel(&this->generateLava(pLoader));
	mPosVbo = (GLuint) pLoader->getLastVbos().y;
	mNormalVbo = (GLuint) pLoader->getLastVbos().z;

	this->loadTextures();
}

Lava::~Lava()
{
}

float Lava::getWorldX() const
{
	return mWorldX;
}

float Lava::getWorldY() const
{
	return mWorldY;
}

float Lava::getWorldZ() const
{
	return mWorldZ;
}

glm::vec3 Lava::getWorldPos() const
{
	return glm::vec3(mWorldX, mWorldY, mWorldZ);
}

const char * Lava::getName()
{
	return mName;
}

void Lava::setName(const char * pName)
{
	mName = pName;
}

glm::mat4 Lava::getModelMatrix()
{
	return Math::getTransformationMatrix(glm::vec3(mWorldX, 0, mWorldZ), 0, 0, 0, 1);
}

Model * Lava::getModel()
{
	return &mModel;
}

void Lava::setModel(Model * pModel)
{
	mModel = *pModel;
}

GLuint Lava::getBurningTexture()
{
	return this->mBurningTexture;
}

Model Lava::generateLava(Loader * loader)
{
	// set grid size
	mGridSize = (float)Lava::LAVA_SIZE / (mVertices - 1);
	int count = mVertices * mVertices;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> textureCoords(count * 2);
	std::vector<int> indices(6 * (mVertices - 1)*(mVertices - 1));
	int vertexPointer = 0;
	for (int z = 0;z<mVertices;z++) {
		for (int x = 0;x<mVertices;x++) {
			vertices[vertexPointer * 3] = (float)x / ((float)mVertices - 1) * Lava::LAVA_SIZE;
			vertices[vertexPointer * 3 + 1] = this->mWorldY;
			vertices[vertexPointer * 3 + 2] = (float)z / ((float)mVertices - 1) * Lava::LAVA_SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
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

	return loader->loadDataToVao(vertices, textureCoords, normals, indices);
}

void Lava::loadTextures()
{
	glGenTextures(1, &mBurningTexture);
	glBindTexture(GL_TEXTURE_2D, mBurningTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
												// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("./lava/res/burning.png", &width, &height, 0, SOIL_LOAD_RGBA);
	if (image == 0)
	{
		std::cout << "The  texture ./lava/res/burning.png could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
