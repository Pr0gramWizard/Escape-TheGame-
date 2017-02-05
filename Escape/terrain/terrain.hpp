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
// Object class
#include "../object/object.hpp"
// FileStream
#include <fstream>
// Standard String 
#include <string>



class Terrain
{
public:
	Terrain(int pGridX, int pGridZ, float pOffset, int pAmplitude, const char* pName, Loader* pLoader, const char* pHeightmap);
	Terrain(int pGridX, int pGridZ, float pOffset, const char* pName, Loader* pLoader, const char* PFilePath);
	~Terrain();
	
	// Loading all important textures
	void loadGrasTexture();
	void loadStoneTexture();
	void loadFlowerTexture();
	void loadMudTexture();
	void loadBlendMapTexture();

	// Getting the texture ID
	GLuint getGrasTexture();
	GLuint getStoneTexture();
	GLuint getFlowerTexture();
	GLuint getMudTexture();
	GLuint getBlendMapTexture();


	// Getter functions
	int getWorldX() const;
	int getWorldZ() const;
	float getOffset() const;
	glm::vec2 getWorldPos() const;
	const char* getName();

	// Setter functions
	void setAmplitude(int pAmplitude);
	void setVertices(int pVertices);
	void setName(const char* pName);


	glm::mat4 getModelMatrix();
	Model* getModel();
	void setModel(Model* pModel);
	GLfloat getHeight(float x, float z);

	glm::vec3 getNormalAt(float x, float z);
		
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
	Model mModel;
	std::vector<float> mHeights;
	// Grass texture
	GLuint mGrassTex;
	// Stone texture
	GLuint mStoneTex;
	// Flower texture
	GLuint mFlowerTex;
	// Mud Texture
	GLuint mMudTex;
	// Blend Map
	GLuint mBlendMapTex;

	// Variables

	// Position
	std::vector<GLfloat> Position;
	// TextureCoords
	std::vector<GLfloat> TextureCoords;
	// Normals
	std::vector<GLfloat> Normals;
	// Indicies
	std::vector<GLint> Indicies;


private:
	bool isPowerOfTwo(int pX);
	Model generateTerrain(Loader* loader);
	void generateHeights(Loader* loader, const char* pHeightmap);
	glm::vec3 computeNormalAt(int x, int z);
	GLfloat getVertexHeight(int pVertexX, int pVertexZ);
	void processVertex(std::vector<std::string> pVertex, std::vector<GLint> pIndicies,std::vector<glm::vec2> pTextureCoordsV, std::vector<glm::vec3> pNormalsV, std::vector<GLfloat> pTextureCoords, std::vector<GLfloat> pNormals);

};

