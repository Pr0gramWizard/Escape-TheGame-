#include "model.hpp"

Model::Model(int pVaoId, int pVertices,int pTextureID)
{
	mVaoId = pVaoId;
	//Amount of vertices
	mVertices = pVertices;
	// Texture ID
	mTextureID = pTextureID;
}

Model::Model(int pVaoId, int pVertices)
{
	mVaoId = pVaoId;
	//Amount of vertices
	mVertices = pVertices;
	// Texture ID
	mTextureID = 0;
}

Model::Model()
{
	mVaoId = 0;
	//Amount of vertices
	mVertices = 0;
	// Texture ID
	mTextureID = 0;
}

Model::~Model()
{
}

int Model::getVaoId() {
	return mVaoId;
}

int Model::getVerticesCount() {
	return mVertices;
}

int Model::getTextureID() {
	return mTextureID;
}

