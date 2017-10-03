#include "model.hpp"

Model::Model() {

}

// Constructor with texture
Model::Model(int pVaoId, int pVertices,int pTextureID)
{
	mVaoId = pVaoId;
	//Amount of vertices
	mVertices = pVertices;
	// Texture ID
	mTextureID = pTextureID;
}

// Constructor with no texture
Model::Model(int pVaoId, int pVertices)
{
	mVaoId = pVaoId;
	//Amount of vertices
	mVertices = pVertices;
	// Texture ID
	mTextureID = 0;
}

// Returns the VertexArrayObject ID
int Model::getVaoId() const {
	return mVaoId;
}

// Returns the number of vertices in the model
int Model::getVerticesCount() const {
	return mVertices;
}

// Returns the texture ID
int Model::getTextureID() const {
	return mTextureID;
}

