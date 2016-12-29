#include "terrain.hpp"

const int Terrain::TERRAIN_SIZE = 5;

Terrain::Terrain(int pGridX, int pGridZ, int pAmplitude, int pVertices, const char* pName, Loader* pLoader)
{
	// Worldspace coordinates
	mWorldX = pGridX * Terrain::TERRAIN_SIZE;
	mWorldZ = pGridZ * Terrain::TERRAIN_SIZE;
	
	// Set height amplitude for terrain
	setAmplitude(pAmplitude);

	// Set amount of vertices along a side of the terrain
	setVertices(pVertices);

	// Name
	setName(pName);


	generateHeights(pLoader);

	// Set Model
	mModel = generateTerrain(pLoader);

	std::cout << "Terrainloader was started successfully!" << std::endl;

}

Terrain::~Terrain()
{
	std::cout << "Terrainloader was stopped successfully!" << std::endl;
}

int Terrain::getWorldX() const
{
	return mWorldX;
}

int Terrain::getWorldZ() const
{
	return mWorldZ;
}

glm::vec2 Terrain::getWorldPos() const
{
	return glm::vec2(mWorldX, mWorldZ);
}

const char * Terrain::getName()
{
	return mName;
}

void Terrain::setAmplitude(int pAmplitude)
{
	mAmplitude = pAmplitude;
}

void Terrain::setVertices(int pVertices)
{
	if (!isPowerOfTwo(pVertices))
	{
		mVertices = 256;
	}
	else
	{
		mVertices = pVertices;
	}
}

void Terrain::setName(const char * pName)
{
	mName = pName;
}

glm::mat4 Terrain::getModelMatrix()
{
	return Math::getTransformationMatrix(glm::vec3(mWorldX, 0, mWorldZ), 0, 0, 0, 1);
}

Model * Terrain::getModel()
{
	return &mModel;
}

void Terrain::setModel(Model * pModel)
{
	mModel = *pModel;
}

bool Terrain::isPowerOfTwo(int pX)
{
	return !(pX == 0) && !(pX & (pX - 1));
}

Model Terrain::generateTerrain(Loader* loader)
{
	int count = mVertices * mVertices;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> textureCoords(count * 2);
	std::vector<int> indices(6 * (mVertices - 1)*(mVertices - 1));
	int vertexPointer = 0;
	for (int i = 0;i<mVertices;i++) {
		for (int j = 0;j<mVertices;j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)mVertices - 1) * Terrain::TERRAIN_SIZE;
			vertices[vertexPointer * 3 + 1] = mHeights[i * mVertices + j];
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)mVertices - 1) * Terrain::TERRAIN_SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)j / ((float)mVertices - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)mVertices - 1);
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

void Terrain::generateHeights(Loader * loader)
{
	// put into Loader
	GLuint heightmap;
	glGenTextures(1, &heightmap);
	int width, height;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, heightmap);
	//height should be equal to width
	unsigned char* image =
		SOIL_load_image("textures/bluetest.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(image);

	std::vector<float> texture_data(width * height);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_FLOAT, &texture_data[0]);

	// put height between -mAmplitude and +mAmplitude
	for (unsigned int i = 0; i < texture_data.size(); ++i)
	{
		texture_data[i] *= 2;
		texture_data[i] -= 1;
		texture_data[i] *= mAmplitude;
	}
	// set mVertices to width!!
	
	mHeights = texture_data;
}
