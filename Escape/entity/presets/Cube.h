#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../entity.hpp"
#include "../../loader/loader.hpp"

class Cube : public Entity
{
public:
	Cube();
	Cube(glm::vec3 pPosition, glm::vec3 pRotation, GLfloat pScale, std::string pCubeTexture);
	Cube(glm::vec3 pPosition, glm::vec3 pRotation, GLfloat pScale);
	Cube(std::string pTexture);
	// Default Destructor
	~Cube();
	// Getter function
	int getVaoId() const;
	int getVerticesCount() const;
	int getTextureID() const;
	// Load texture
	void loadTexture(std::string pTexturePath);


// Cube Data
public:
	static std::unique_ptr<Loader> sLoader;
	static std::vector<float> sCubeVertices;
	static std::vector<int> sCubeIndicies;
	static std::vector<float> sCubeTextureCoordinates;
	static std::vector<float> sCubeNormals;

private:
	// VertexArrayObject ID
	GLuint mVaoId;
	// Number of vertices
	GLuint mVertices;
	// Texture ID
	GLuint mTextureID;
	// VertexBufferObject ID
	GLuint mVboId;
};

