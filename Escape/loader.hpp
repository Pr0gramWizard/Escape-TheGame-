#pragma once
// Inclusion of all important libraries

// Standard Input/Output
#include <iostream>
// OpenGLExtensionWrangler libary
#include <glew.h>
// List
#include <list>
// Vector
#include <vector>
// Model class
#include "model.hpp"
// Math class
#include "math.hpp"
// Simple OpenGL Image Loader
#include <SOIL.h>

// Declaration of the loader class
class Loader
{
// All public functions
public:
	// Default Constructor
	Loader();
	// Default Destructor
	~Loader();
	// Function loads raw data to Model (with texture)
	Model loadDataToVao(std::vector<float> pPositions, std::vector<float> pTexCoords, std::vector<float> pNormals, std::vector<int> pIndices, const char* pTextureFile);
	// Function loads raw data to Model
	Model loadDataToVao(std::vector<float> pPositions, std::vector<float> pTexCoords, std::vector<float> pNormals, std::vector<int> pIndices);
	// Function cleans up all the mess after creating the VertexArrayObjects
	void cleanUp();

// All private functions
private:
	// Creates a VertexArrayObject
	GLuint createVao();
	// Unbinds the VertexArrayObject
	void unbindVao();
	// Stores the data in a certain location in the VertexBufferObject
	void storeData(GLuint pAttributeLocation, std::vector<float> pData, int pLength,GLuint pOffSet);
	// Loads the texture
	GLuint loadTexture(const char* pFileName);
	// Deletes all VertexArrayObject
	void deleteVaos();
	// Deletes all VertexBufferObjects
	void deleteVbos();
	// Deletes all TextureObjects
	void deleteTextures();
	// Creates a VertexBufferObject for the indices
	void bindIndices(std::vector<int> pIndices);
// All private member
private:
	// List of all VertexArrayObjects
	std::list<GLuint> mVaos;
	// List of all VertexBufferObjects
	std::list<GLuint> mVbos;
	// List of all TextureObjects
	std::list<GLuint> mTextures;
};

