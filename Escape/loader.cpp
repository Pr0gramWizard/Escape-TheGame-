// Inclustion of the declaration
#include "loader.hpp"

// Default constructor
Loader::Loader()
{
	mLastVbos = glm::vec4(-1, -1, -1, -1);
	// Log Message
	std::cout << "Loader instance was created successfully!" << std::endl;
}

// Default Destructor
Loader::~Loader()
{
	// Log Message
	std::cout << "Loader instance was destroyed successfully!" << std::endl;
}

// Loads raw Data (Vertices,Texture,Normals,Indices) into a Model
Model Loader::loadDataToVao(std::vector<float> pPositions, std::vector<float> pTexCoords, std::vector<float> pNormals, std::vector<int> pIndices,const char* pTextureFile)
{
	// Creates new VertexArrayObject
	GLuint vaoId = createVao();
	// Binding the indices to a VertexBufferObject
	bindIndices(pIndices);
	// Store the vertices in the 0th position in the VertexBufferObject
	storeData(0, pPositions, 3);
	// Store the normal coordiantes in the 1th position in the VertexBufferObject
	storeData(1, pNormals, 3);
	// Store the texture coordiantes in the 2th position in the VertexBufferObject
	storeTexture(2, pTexCoords, 2);
	GLuint textureID = loadTexture(pTextureFile);
	// Unbinds the current VertexArrayObject
	unbindVao();
	// Returns a model with given VertexArrayObject ID and the number of triangles
	return Model(vaoId, pIndices.size(),textureID);
}

// Loads raw Data (Vertices,Texture,Normals,Indices) into a VertexArrayObject
Model Loader::loadDataToVao(std::vector<float> pPositions, std::vector<float> pTexCoords, std::vector<float> pNormals, std::vector<int> pIndices)
{
	// Creates new VertexArrayObject
	GLuint vaoId = createVao();
	// Binding the indices to a VertexBufferObject
	bindIndices(pIndices);
	// Store the vertices in the 0th position in the VertexBufferObject
	storeData(0, pPositions, 3);
	// Store the normal coordiantes in the 1th position in the VertexBufferObject
	storeData(1, pNormals, 3);
	// Unbinds the current VertexArrayObject
	unbindVao();
	// Returns a model with given VertexArrayObject ID and the number of triangles
	return Model(vaoId, pIndices.size());
}


// Creates a VertexArrayObject and returns the ID
GLuint Loader::createVao()
{
	GLuint vao;
	// Create new empty VertexArray
	glGenVertexArrays(1, &vao);
	// Add current VertexArrayObject to the list of all VertexArrayObjects
	mVaos.push_back(vao);
	// Bind the Vertex Array to the current Object
	glBindVertexArray(vao);
	// Return the ID
	return vao;
}

// Unbind the current VertexArrayObject
void Loader::unbindVao()
{
	// By binding to 0 we automatically unbind it from the current instance
	glBindVertexArray(0);
}

// Bind indices into VertexBufferObject
void Loader::bindIndices(std::vector<int> pIndices) {
	GLuint vbo;
	// Create new empty BufferObject
	glGenBuffers(1, &vbo);
	// Add current VertexBufferObject to the list of all VertexBufferObjects
	mVbos.push_back(vbo);
	// Save vbo
	mLastVbos.x = vbo;
	// Bind Buffer to VertexBufferObject
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	// Buffer the data to the graphics card
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndices.size() * sizeof(int), &pIndices[0], GL_STATIC_DRAW);
}

// Storing the vertices in a VertexBufferObject
void Loader::storeData(GLuint pAttributeLocation, std::vector<float> pData, GLuint pSize)
{
	GLuint vbo;
	// Create new empty BufferObject
	glGenBuffers(1, &vbo);
	// Add current VertexBufferObject to the list of all VertexBufferObjects
	mVbos.push_back(vbo);
	if (pAttributeLocation == 0)
	{
		mLastVbos.y = vbo;
	}
	else if (pAttributeLocation == 1)
	{
		mLastVbos.z = vbo;
	}
	else if (pAttributeLocation == 2)
	{
		mLastVbos.w = vbo;
	}
	// Bind Buffer to VertexBufferObject
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Buffer the data to the graphics card
	glBufferData(GL_ARRAY_BUFFER, pData.size() * sizeof(float),	&pData[0], GL_STATIC_DRAW);
	// Specify the poistion of the current data in the VertexBufferObject
	glVertexAttribPointer(pAttributeLocation, pSize, GL_FLOAT, GL_FALSE, pSize * sizeof(float), (GLvoid*)0);
	// Unbind the VertexBufferObject
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Storing the vertices in a VertexBufferObject
void Loader::storeTexture(GLuint pAttributeLocation, std::vector<float> pData, GLuint pSize)
{
	GLuint vbo;
	// Create new empty BufferObject
	glGenBuffers(1, &vbo);
	// Add current VertexBufferObject to the list of all VertexBufferObjects
	mVbos.push_back(vbo);
	// Bind Buffer to VertexBufferObject
	glBindBuffer(GL_TEXTURE_COORD_ARRAY, vbo);
	// Buffer the data to the graphics card
	glBufferData(GL_TEXTURE_COORD_ARRAY, pData.size() * sizeof(float), &pData[0], GL_STATIC_DRAW);
	// Specify the poistion of the current data in the VertexBufferObject
	glTexCoordPointer(pAttributeLocation, GL_FLOAT, pSize * sizeof(float), (GLvoid*)0);
	// Unbind the VertexBufferObject
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



	GLuint Loader::loadTexture(const char * pFileName)
{
	int width, height;
	// Loading the image with SOIL
	unsigned char* image = SOIL_load_image(pFileName, &width, &height, 0, SOIL_LOAD_RGB);

	GLuint TextureID;
	// Creating new empty texture object
	glGenTextures(1, &TextureID);
	// Binding a 2D Texture to the object
	glBindTexture(GL_TEXTURE_2D, TextureID);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Setting Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// Adding Texture ID to the list
	mTextures.push_back(TextureID);
	// Declaration of image width/height

	// Relocate the image resources
	SOIL_free_image_data(image);
	
	return TextureID;

}

// Delete all VertexArrayObjects
void Loader::deleteVaos() 
{
	// Loop trough the list of all VertexArrayObjects and delete them
	for (GLuint vao : mVaos)
	{
		glDeleteVertexArrays(1, &vao);
	}
}

// Delete all VertexBufferObjects
void Loader::deleteVbos() 
{
	// Loop trough the list of all VertexBufferObjects and delete them
	for (GLuint vbo : mVbos) 
	{
		glDeleteBuffers(1, &vbo);
	}
}

// Delete all VertexBufferObjects
void Loader::deleteTextures()
{
	// Loop trough the list of all VertexBufferObjects and delete them
	for (GLuint texture : mTextures)
	{
		glDeleteBuffers(1, &texture);
	}
}

glm::vec4 Loader::getLastVbos()
{
	return mLastVbos;
}

// Clean up all the mess
void Loader::cleanUp() {
	// Unbind VertexArrayObject
	unbindVao();
	// Delete all VertexArrayObjects
	deleteVaos();
	// Delete all VertexBufferObjects
	deleteVbos();
	// Delete all TextureObjects
	deleteTextures();
}