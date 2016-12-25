// Inclustion of the declaration
#include "loader.hpp"

// Default constructor
Loader::Loader()
{
	// Log Message
	std::cout << "Loader instance was created successfully!" << std::endl;
}

// Default Destructor
Loader::~Loader()
{
	// Log Message
	std::cout << "Loader instance was destroyed successfully!" << std::endl;
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
	/*storeData(1, pNormals, 3);*/
	// Store the texture coordiantes in the 2th position in the VertexBufferObject
	/*storeData(2, pTexCoords, 2);*/
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
	// Bind Buffer to VertexBufferObject
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	// Buffer the data to the graphics card
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndices.size() * sizeof(int), &pIndices[0], GL_STATIC_DRAW);
}

// Storing the vertices in a VertexBufferObject
void Loader::storeData(GLuint pAttributeLocation, std::vector<float> pData, int pSize)
{
	GLuint vbo;
	// Create new empty BufferObject
	glGenBuffers(1, &vbo);
	// Add current VertexBufferObject to the list of all VertexBufferObjects
	mVbos.push_back(vbo);
	// Bind Buffer to VertexBufferObject
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Buffer the data to the graphics card
	glBufferData(GL_ARRAY_BUFFER, pData.size() * sizeof(float),	&pData[0], GL_STATIC_DRAW);
	// Specify the poistion of the current data in the VertexBufferObject
	glVertexAttribPointer(pAttributeLocation, pSize, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	// Unbind the VertexBufferObject
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

// Clean up all the mess
void Loader::cleanUp() {
	// Unbind VertexArrayObject
	unbindVao();
	// Delete all VertexArrayObjects
	deleteVaos();
	// Delete all VertexBufferObjects
	deleteVbos();
}