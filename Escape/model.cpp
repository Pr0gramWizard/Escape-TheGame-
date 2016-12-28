#include "model.hpp"

Model::Model(int pVaoId, int pVertices)
{
	mVaoId = pVaoId;
	//Amount of vertices
	mVertices = pVertices;
}

Model::Model()
{
	mVaoId = 0;
	//Amount of vertices
	mVertices = 0;
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
