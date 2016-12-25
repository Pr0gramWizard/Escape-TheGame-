#pragma once
class Model
{
public:
	Model(int pVaoId, int pVertices);
	~Model();

	int getVaoId();
	int getVerticesCount();

private:
	int mVaoId;
	int mVertices;
};

