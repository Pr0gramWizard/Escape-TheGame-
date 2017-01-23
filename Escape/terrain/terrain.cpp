#include "terrain.hpp"

const int Terrain::TERRAIN_SIZE = 512;

Terrain::Terrain(int pGridX, int pGridZ, float pOffset, int pAmplitude, const char* pName, Loader* pLoader, const char* pHeightmap)
{
	// Worldspace coordinates
	mWorldX = pGridX * Terrain::TERRAIN_SIZE;
	mWorldZ = pGridZ * Terrain::TERRAIN_SIZE;
	mOffset = pOffset;
	
	// Set height amplitude for terrain
	setAmplitude(pAmplitude);

	// Name
	setName(pName);

	// Generate heights for the terrain & set mVertices acording to heightmap 
	generateHeights(pLoader, pHeightmap);

	// Set Model
	mModel = generateTerrain(pLoader);

	this->loadGrasTexture();
	this->loadStoneTexture();
	this->loadFlowerTexture();
	this->loadMudTexture();
	this->loadBlendMapTexture();


	std::cout << "Terrainloader was started successfully!" << std::endl;

}

Terrain::~Terrain()
{
	std::cout << "Terrainloader was stopped successfully!" << std::endl;
}

void Terrain::loadGrasTexture()
{
	glGenTextures(1, &mGrassTex);
	glBindTexture(GL_TEXTURE_2D, mGrassTex); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* grass = SOIL_load_image("terrain/res/texture/grass.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (grass == 0)
	{
		std::cout << "The gras texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(grass);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Terrain::loadStoneTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &mStoneTex);
	glBindTexture(GL_TEXTURE_2D, mStoneTex); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* stone = SOIL_load_image("terrain/res/texture/stone.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (stone == 0)
	{
		std::cout << "The stone texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, stone);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(stone);
	glBindTexture(GL_TEXTURE_2D, 0);


}

void Terrain::loadFlowerTexture()
{
	glGenTextures(1, &mFlowerTex);
	glBindTexture(GL_TEXTURE_2D, mFlowerTex); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* grass = SOIL_load_image("terrain/res/texture/flower.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (grass == 0)
	{
		std::cout << "The flower texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(grass);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Terrain::loadMudTexture()
{
	glGenTextures(1, &mMudTex);
	glBindTexture(GL_TEXTURE_2D, mMudTex); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* grass = SOIL_load_image("terrain/res/texture/mud.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (grass == 0)
	{
		std::cout << "The mud texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(grass);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Terrain::loadBlendMapTexture()
{
	glGenTextures(1, &mBlendMapTex);
	glBindTexture(GL_TEXTURE_2D, mBlendMapTex); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* grass = SOIL_load_image("terrain/res/texture/blendmap.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (grass == 0)
	{
		std::cout << "The blendmap texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(grass);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Terrain::getWorldX() const
{
	return mWorldX;
}

int Terrain::getWorldZ() const
{
	return mWorldZ;
}

int Terrain::getOffset() const
{
	return mOffset;
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
	mVertices = pVertices;
}

void Terrain::setName(const char * pName)
{
	mName = pName;
}

GLuint Terrain::getGrasTexture()
{
	return mGrassTex;
}

GLuint Terrain::getStoneTexture()
{
	return mStoneTex;
}

GLuint Terrain::getFlowerTexture()
{
	return mFlowerTex;
}

GLuint Terrain::getMudTexture()
{
	return mMudTex;
}

GLuint Terrain::getBlendMapTexture()
{
	return mBlendMapTex;
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
	// set grid size
	mGridSize = (float) Terrain::TERRAIN_SIZE/(mVertices - 1);
	int count = mVertices * mVertices;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> textureCoords(count * 2);
	std::vector<int> indices(6 * (mVertices - 1)*(mVertices - 1));
	int vertexPointer = 0;
	for (int z = 0;z<mVertices;z++) {
		for (int x = 0;x<mVertices;x++) {
			vertices[vertexPointer * 3] = (float)x / ((float)mVertices - 1) * Terrain::TERRAIN_SIZE;
			vertices[vertexPointer * 3 + 1] = this->getVertexHeight(x, z);
			vertices[vertexPointer * 3 + 2] = (float)z / ((float)mVertices - 1) * Terrain::TERRAIN_SIZE;
			glm::vec3 normal = this->computeNormalAt(x, z);
			// if(x == z) std::cout << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
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

void Terrain::generateHeights(Loader * loader, const char* pHeightmap)
{
	// put into Loader
	GLuint heightmap;
	glGenTextures(1, &heightmap);
	int width, height;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, heightmap);
	// height should be equal to width
	unsigned char* image = SOIL_load_image(pHeightmap, &width, &height, 0, SOIL_LOAD_RGB);

	if (image == 0)
	{
		std::cout << "Could not find the heightmap!" << std::endl;
	}
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
		// Add height offset;
		texture_data[i] += mOffset;
	}

	// Set amount of vertices along a side of the terrain
	this->setVertices(width);

	mHeights = texture_data;
}

GLfloat Terrain::getHeight(float x, float z) {
	float xPosRelativeToTerrain = x - mWorldX;
	float zPosRelativeToTerrain = z - mWorldX;

	int gridX = floor(xPosRelativeToTerrain / mGridSize);
	int gridZ = floor(zPosRelativeToTerrain / mGridSize);

	if (gridX < 0 || gridZ < 0 || gridX >= mVertices - 1 || gridZ >= mVertices - 1)
	{
		return 0.0f;
	}

	// position within the grid square between 0 and 1
	float dX = fmod(xPosRelativeToTerrain, mGridSize) / mGridSize;
	float dZ = fmod(zPosRelativeToTerrain, mGridSize) / mGridSize;

	if (dX <= (1 - dZ)) {
		return Math::barryCentricHeight(
			glm::vec3(0, mHeights[gridZ * mVertices + gridX], 0),
			glm::vec3(1, mHeights[gridZ * mVertices + (gridX + 1)], 0),
			glm::vec3(0, mHeights[(gridZ + 1) * mVertices + gridX], 1),
			glm::vec2(dX, dZ)
		);
	}
	else {
		return Math::barryCentricHeight(
			glm::vec3(1, mHeights[gridZ * mVertices + (gridX + 1)], 0),
			glm::vec3(1, mHeights[(gridZ + 1) * mVertices + (gridX + 1)], 1),
			glm::vec3(0, mHeights[(gridZ + 1) * mVertices + gridX], 1),
			glm::vec2(dX, dZ)
		);
	}
}

GLfloat Terrain::getVertexHeight(int pVertexX, int pVertexZ)
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

glm::vec3 Terrain::computeNormalAt(int x, int z)
{
	/*float abstand = Terrain::TERRAIN_SIZE / ((float)mVertices - 1);
	glm::vec3 point = glm::vec3(mWorldX + x*abstand, this->getVertexHeight(x, z), mWorldZ + z*abstand);
	glm::vec3 vLeft = glm::normalize(glm::vec3(point.x - abstand, this->getVertexHeight(x - 1, z), point.z));
	glm::vec3 vRight = glm::normalize(glm::vec3(point.x + abstand, this->getVertexHeight(x + 1, z), point.z));
	glm::vec3 vDown = glm::normalize(glm::vec3(point.x, this->getVertexHeight(x, z - 1), point.z - abstand));
	glm::vec3 vUp = glm::normalize(glm::vec3(point.x, this->getVertexHeight(x, z + 1), point.z + abstand));

	glm::vec3 vLD = glm::normalize(glm::cross(vLeft, vDown));
	glm::vec3 vLU = glm::normalize(glm::cross(vLeft, vUp));
	glm::vec3 vRD = glm::normalize(glm::cross(vRight, vDown));
	glm::vec3 vRU = glm::normalize(glm::cross(vRight, vUp));

	glm::vec3 normal = glm::normalize(vLD + vLU + vRD + vRU);
	return normal;*/

	// read neightbor heights using an arbitrary small offset
	float hL = this->getVertexHeight(x - 1, z);
	float hR = this->getVertexHeight(x + 1, z);
	float hD = this->getVertexHeight(x, z - 1);
	float hU = this->getVertexHeight(x, z + 1);

	// deduce terrain normal
	glm::vec3 normal = glm::vec3(hL - hR, 2.0f, hD - hU);

	return glm::normalize(normal);
}