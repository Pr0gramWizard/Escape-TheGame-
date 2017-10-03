#pragma once
#include <iostream>

// Class defintion: Model
class Model
{
// Public functions
public:
	// Default constructor
	Model();
	// Constructor with all parameters
	Model(int pVaoId, int pVertices, int pTextureId);
	// Constructor with no texture
	Model(int pVaoId, int pVertices);

	// Getter function
	int getVaoId() const;
	int getVerticesCount() const;
	int getTextureID() const;

// Private variables
private:
	// VertexArrayObject ID
	int mVaoId;
	// Number of vertices
	int mVertices;
	// Texture ID
	int mTextureID;
};

