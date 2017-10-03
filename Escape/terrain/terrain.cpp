#include "terrain.hpp"

const int Terrain::TERRAIN_SIZE = 256;

Terrain::Terrain(int pGridX, int pGridZ, float pOffset, int pAmplitude, const char* pName, Loader* pLoader, const char* pHeightmap, unsigned int pTerrainSize)
{

	mWorldX = pGridX * Terrain::TERRAIN_SIZE;
	mWorldZ = pGridZ * Terrain::TERRAIN_SIZE;
	mOffset = pOffset;
	
	// Set height amplitude for terrain
	setAmplitude(pAmplitude);

	// Name
	setName(pName);

	// Generate heights for the terrain & set mVertices acording to heightmap 

	// generateHeights(pLoader, pHeightmap);
	generateRandomHeights(pTerrainSize);

	// this->setChunkSize(pChunkSize);
	// generateChunks(mChunkSize);

	// Set Model
	mModel = generateTerrain(pLoader,false);

	// this->loadBlueTexture(pTexturePacks.at(0).c_str());
	// this->loadRedTexture(pTexturePacks.at(1).c_str());
	// this->loadCyanTexture(pTexturePacks.at(2).c_str());
	// this->loadPurpleTexture(pTexturePacks.at(3).c_str());
	// this->loadBlendMapTexture(pTexturePacks.at(4).c_str());


	std::cout << "Terrainloader was started successfully!" << std::endl;

}

void Terrain::redrawTerrain(Loader* pLoader, unsigned int pTerrainSize) {
	generateRandomHeights(pTerrainSize);
	mModel = generateTerrain(pLoader, false);
}

Terrain::Terrain(int pGridX, int pGridZ, float pOffset, const char * pName, Loader * pLoader, const char* pFilePath)
{
	mWorldX = pGridX * Terrain::TERRAIN_SIZE;
	mWorldZ = pGridZ * Terrain::TERRAIN_SIZE;
	mOffset = pOffset;

	// Name
	setName(pName);

	// Position Vector
	std::vector<glm::vec3> PositionV;
	// TextureCoords Vector
	std::vector<glm::vec2> TextureCoordsV;
	// Normals Vector
	std::vector<glm::vec3> NormalsV;
	// Indicies Vector
	std::vector<GLint> IndiciesV;



	std::ifstream File(pFilePath);
	std::string content;

	std::string delimiter = " ";
	std::string delimiterF = "/";
	size_t pos1 = 0;
	size_t pos2 = 0;
	size_t posT1 = 0;
	size_t posT2 = 0;
	size_t posT3 = 0;

	if (File.fail())
	{
		std::cout << "The file " << pFilePath << " could not be founded!" << std::endl;
	}
	else
	{
		while (std::getline(File, content))
		{
			if (content.at(0) == '#' || content.at(0) == 'o' || content.at(0) == 's' || content.at(0) == 'l')
			{
				continue;
			}

			if (content.at(0) == 'f')
			{
				// Temp Store for the current line
				std::vector<std::string> faceLine;
				// Searching for a space character
				while ((pos2 = content.find(delimiter)) != std::string::npos)
				{
					// Add content to vector
					faceLine.push_back(content.substr(0, pos2));
					content.erase(0, pos2 + delimiter.length());
				}

				faceLine.push_back(content);

				std::vector<std::string> vertex1;
				std::vector<std::string> vertex2;
				std::vector<std::string> vertex3;

				// Vertex 1
				while ((posT1 = faceLine.at(1).find(delimiterF)) != std::string::npos)
				{
					// Add content to vector
					vertex1.push_back(faceLine.at(1).substr(0, posT1));
					faceLine.at(1).erase(0, posT1 + delimiterF.length());
				}

				vertex1.push_back(faceLine.at(1));

				// Vertex 2
				while ((posT2 = faceLine.at(2).find(delimiterF)) != std::string::npos)
				{
					// Add content to vector
					vertex2.push_back(faceLine.at(2).substr(0, posT2));
					faceLine.at(2).erase(0, posT2 + delimiterF.length());
				}

				vertex2.push_back(faceLine.at(2));

				// Vertex 3
				while ((posT3 = faceLine.at(3).find(delimiterF)) != std::string::npos)
				{
					// Add content to vector
					vertex3.push_back(faceLine.at(3).substr(0, posT3));
					faceLine.at(3).erase(0, posT3 + delimiterF.length());
				}

				vertex3.push_back(faceLine.at(3));

				// Add Data
				// Vertex 1
				int currentVertexPointer1 = stoi(vertex1.at(0)) - 1;

				// Add Indicies
				Indicies.push_back(currentVertexPointer1);

				// Add Texture Coordinates
				glm::vec2 currentTex1 = TextureCoordsV.at(stoi(vertex1[1]) - 1);
				TextureCoords.push_back(currentTex1.x);
				TextureCoords.push_back(currentTex1.y);

				// Add Normal Vectors
				glm::vec3 currentNorm1 = NormalsV.at(stoi(vertex1[2]) - 1);

				Normals.push_back(currentNorm1.x);
				Normals.push_back(currentNorm1.y);
				Normals.push_back(currentNorm1.z);

				// Vertex 2
				int currentVertexPointer2 = stoi(vertex2.at(0)) - 1;

				// Add Indicies
				Indicies.push_back(currentVertexPointer2);

				// Add Texture Coordinates
				glm::vec2 currentTex2 = TextureCoordsV.at(stoi(vertex2[1]) - 1);
				TextureCoords.push_back(currentTex2.x);
				TextureCoords.push_back(currentTex2.y);

				// Add Normal Vectors
				glm::vec3 currentNorm2 = NormalsV.at(stoi(vertex2[2]) - 1);

				Normals.push_back(currentNorm2.x);
				Normals.push_back(currentNorm2.y);
				Normals.push_back(currentNorm2.z);

				// Vertex 3
				int currentVertexPointer3 = stoi(vertex3.at(0)) - 1;

				// Add Indicies
				Indicies.push_back(currentVertexPointer3);

				// Add Texture Coordinates
				glm::vec2 currentTex3 = TextureCoordsV.at(stoi(vertex3[1]) - 1);
				TextureCoords.push_back(currentTex3.x);
				TextureCoords.push_back(currentTex3.y);

				// Add Normal Vectors
				glm::vec3 currentNorm3 = NormalsV.at(stoi(vertex3[2]) - 1);

				Normals.push_back(currentNorm3.x);
				Normals.push_back(currentNorm3.y);
				Normals.push_back(currentNorm3.z);

			}
			else
			{			
				// Temp Store for the current line
				std::vector<std::string> currentLine;
				// Searching for a space character
				while ((pos1 = content.find(delimiter)) != std::string::npos)
				{
					// Add content to vector
					currentLine.push_back(content.substr(0, pos1));
					content.erase(0, pos1 + delimiter.length());
				}

				// Add last content to vector
				currentLine.push_back(content);

				// Line is vertex
				if (currentLine.at(0).at(0) == 'v' && currentLine.at(0).size() == 1)
				{
					glm::vec3 vertex(stof(currentLine[1]), stof(currentLine[2]), stof(currentLine[3]));
					PositionV.push_back(vertex);

				}
				// Line is vertex texture
				else  if (currentLine.at(0).at(1) == 't')
				{
					glm::vec2 texcoord(stof(currentLine[1]), stof(currentLine[2]));
					TextureCoordsV.push_back(texcoord);
				}
				// Line is vertex normal
				else  if (currentLine.at(0).at(1) == 'n')
				{
					glm::vec3 normal(stof(currentLine[1]), stof(currentLine[2]), stof(currentLine[3]));
					NormalsV.push_back(normal);
				}
			}
			
		}
	}



	for (glm::vec3 Vertex : PositionV)
	{
		// Finish postion vector
		Position.push_back(Vertex.x);
		Position.push_back(Vertex.y + mOffset);
		Position.push_back(Vertex.z);
		// Create heights
		mHeights.push_back(Vertex.y + mOffset);
	}

	std::cout << Position.size() / 3 << std::endl;

	mGridSize = (float)Terrain::TERRAIN_SIZE / ((Position.size() / 3) - 1);
	mVertices = (int) sqrt((Position.size() / 3));

	// Set Model
	mModel = pLoader->loadDataToVao(Position, TextureCoords, Normals, Indicies);
}

Terrain::~Terrain()
{
	std::cout << "Terrainloader was stopped successfully!" << std::endl;
}

void Terrain::loadBlueTexture(const char* pFilePath)
{
	glGenTextures(1, &mBlueTexture);
	glBindTexture(GL_TEXTURE_2D, mBlueTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(pFilePath, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == 0)
	{
		std::cout << "The  texture " << pFilePath << " could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Terrain::loadRedTexture(const char* pFilePath)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &mRedTexture);
	glBindTexture(GL_TEXTURE_2D, mRedTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(pFilePath, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == 0)
	{
		std::cout << "The  texture " << pFilePath << " could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


}
void Terrain::loadTransparentMap(const char* pFilePath)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &mTransparentMap);
	glBindTexture(GL_TEXTURE_2D, mTransparentMap); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(pFilePath, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == 0)
	{
		std::cout << "The  texture " << pFilePath << " could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


}
void Terrain::loadCyanTexture(const char* pFilePath)
{
	glGenTextures(1, &mCyanTexture);
	glBindTexture(GL_TEXTURE_2D, mCyanTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(pFilePath, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == 0)
	{
		std::cout << "The  texture " << pFilePath << " could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Terrain::loadPurpleTexture(const char* pFilePath)
{
	glGenTextures(1, &mPurpleTexture);
	glBindTexture(GL_TEXTURE_2D, mPurpleTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(pFilePath, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == 0)
	{
		std::cout << "The  texture " << pFilePath << " could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Terrain::loadBlendMapTexture(const char* pFilePath)
{
	glGenTextures(1, &mBlendMapTex);
	glBindTexture(GL_TEXTURE_2D, mBlendMapTex); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(pFilePath, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == 0)
	{
		std::cout << "The  texture " << pFilePath << " could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
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

float Terrain::getOffset() const
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

GLuint Terrain::getBlueTexture()
{
	return mBlueTexture;
}

GLuint Terrain::getRedTexture()
{
	return mRedTexture;
}

GLuint Terrain::getCyanTexture()
{
	return mCyanTexture;
}

GLuint Terrain::getPurpleTexture()
{
	return mPurpleTexture;
}

GLuint Terrain::getBlendMapTexture()
{
	return mBlendMapTex;
}

GLuint Terrain::getTransparentTexture()
{
	return mTransparentMap;
}

glm::mat4 Terrain::getModelMatrix()
{
	return Math::getTransformationMatrix(glm::vec3(mWorldX, 0, mWorldZ), 0, 0, 0, 1);
}

Model * Terrain::getModel()
{
	return &mModel;
}

unsigned int Terrain::getChunkSize() const {
	return mChunkSize;
	}

void Terrain::setChunkSize(unsigned int pChunkSize) {
	mChunkSize = pChunkSize;
}
void Terrain::setModel(Model * pModel)
{
	mModel = *pModel;
}

bool Terrain::isPowerOfTwo(int pX)
{
	return !(pX == 0) && !(pX & (pX - 1));
}

Model Terrain::generateTerrain(Loader* loader, bool isCeiling)
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

	if (isCeiling)
	{
		for (unsigned int i = 0; i < normals.size(); ++i)
		{
			normals.at(i) = -1 * normals.at(i);
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
		return;
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
		texture_data[i] *= 4;
		texture_data[i] -= 1;
		texture_data[i] *= mAmplitude;
		// Add height offset;
		texture_data[i] += mOffset;
	}
	// Set amount of vertices along a side of the terrain
	this->setVertices(width);

	mHeights = texture_data;
}

void Terrain::generateRandomHeights(unsigned int size) {
	TerrainGenerator* test = new TerrainGenerator(size, size, 1.0f,10,0.5f,2.0f);
	this->setVertices(size);
	mHeights = test->getHeightValues();
	std::cout << "Random Terrain generated!" << std::endl;
}

GLfloat Terrain::getHeight(float x, float z) {
	float xPosRelativeToTerrain = x - mWorldX;
	float zPosRelativeToTerrain = z - mWorldX;

	int gridX = (int) floor(xPosRelativeToTerrain / mGridSize);
	int gridZ = (int) floor(zPosRelativeToTerrain / mGridSize);

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

glm::vec3 Terrain::getNormalAt(float x, float z) {
	float xPosRelativeToTerrain = x - mWorldX;
	float zPosRelativeToTerrain = z - mWorldX;

	int gridX = (int) floor(xPosRelativeToTerrain / mGridSize);
	int gridZ = (int) floor(zPosRelativeToTerrain / mGridSize);

	if (gridX < 0 || gridZ < 0 || gridX >= mVertices - 1 || gridZ >= mVertices - 1)
	{
		return glm::vec3(0.0f);
	}

	// position within the grid square between 0 and 1
	float dX = fmod(xPosRelativeToTerrain, mGridSize) / mGridSize;
	float dZ = fmod(zPosRelativeToTerrain, mGridSize) / mGridSize;

	if (dX <= (1 - dZ)) {
		return normalize(this->computeNormalAt(gridX, gridZ) + this->computeNormalAt(gridX + 1, gridZ) + this->computeNormalAt(gridX, gridZ + 1));
	}
	else {
		return normalize(this->computeNormalAt(gridX + 1, gridZ) + this->computeNormalAt(gridX + 1, gridZ + 1) + this->computeNormalAt(gridX, gridZ + 1));
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