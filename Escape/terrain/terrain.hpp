#pragma once
// OpenGLExtensionWrangler
#include <glew.h>
// Standard Input/Output Stream
#include <iostream>
// 2x1 Vector
#include <vec2.hpp>
// Standard Vector
#include <vector>
// Model class
#include "../model/model.hpp"
// Loader class
#include "../loader/loader.hpp"
// Math class
#include "../math/math.hpp"
// FileStream
#include <fstream>
// Standard String 
#include <string>
// Random 
#include <random>



class Terrain
{
public:
	Terrain(int pGridX, int pGridZ, float pOffset, int pAmplitude, const char* pName, Loader* pLoader, const char* pHeightmap, bool isCeiling, unsigned int chunkSize, unsigned int pTerrainSize);
	Terrain(int pGridX, int pGridZ, float pOffset, const char* pName, Loader* pLoader, const char* PFilePath);
	~Terrain();
	
	// Loading all important textures
	void loadBlueTexture(const char* pBlendMapPath);
	void loadRedTexture(const char* pBlendMapPath);
	void loadCyanTexture(const char* pBlendMapPath);
	void loadPurpleTexture(const char* pBlendMapPath);
	void loadBlendMapTexture(const char* pBlendMapPath);
	void loadTransparentMap(const char* pBlendMapPath);

	// Getting the texture ID
	GLuint getBlueTexture();
	GLuint getRedTexture();
	GLuint getCyanTexture();
	GLuint getPurpleTexture();
	GLuint getBlendMapTexture();
	GLuint getTransparentTexture();


	// Getter functions
	int getWorldX() const;
	int getWorldZ() const;
	float getOffset() const;
	const char* getName();
	glm::vec2 getWorldPos() const;
	glm::vec3 getNormalAt(float x, float z);
	glm::mat4 getModelMatrix();
	Model* getModel();
	GLfloat getHeight(float x, float z);
	unsigned int getChunkSize() const;


	// Setter functions
	void setAmplitude(int pAmplitude);
	void setVertices(int pVertices);
	void setName(const char* pName);
	void setModel(Model* pModel);
	void setChunkSize(unsigned int pChunkSize);
		
public:
	static const int TERRAIN_SIZE;

private:
	int mWorldX;
	int mWorldZ;
	// Height offset
	float mOffset;
	int mAmplitude;
	// Getters & Setters needed? Maybe static
	int mVertices;
	float mGridSize;
	const char* mName;
	unsigned int mChunkSize;
	Model mModel;
	std::vector<float> mHeights;
	// Grass texture
	GLuint mBlueTexture;
	// Stone texture
	GLuint mRedTexture;
	// Flower texture
	GLuint mCyanTexture;
	// Mud Texture
	GLuint mPurpleTexture;
	// Blend Map
	GLuint mBlendMapTex;
	// Transparent Map
	GLuint mTransparentMap;

	// Variables

	// Position
	std::vector<GLfloat> Position;
	// TextureCoords
	std::vector<GLfloat> TextureCoords;
	// Normals
	std::vector<GLfloat> Normals;
	// Indicies
	std::vector<GLint> Indicies;
	// Chunk Coordinates
	std::vector<std::vector<std::vector<int> > > mChunks;


private:
	bool isPowerOfTwo(int pX);
	Model generateTerrain(Loader* loader, bool isCeiling = false);
	void generateHeights(Loader* loader, const char* pHeightmap);
	glm::vec3 computeNormalAt(int x, int z);
	GLfloat getVertexHeight(int pVertexX, int pVertexZ);
	void generateRandomHeights(Loader* pLoader, unsigned int size);
	void generateChunks(unsigned int pChunksize);
};

