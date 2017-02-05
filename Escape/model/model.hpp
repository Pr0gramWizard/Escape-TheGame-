#pragma once
class Model
{
public:
	Model();
	Model(int pVaoId, int pVertices, int pTextureId);
	Model(int pVaoId, int pVertices);
	~Model();

	int getVaoId();
	int getVerticesCount();
	int getTextureID();

private:
	int mVaoId;
	int mVertices;
	int mTextureID;
};

