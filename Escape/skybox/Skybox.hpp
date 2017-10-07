#pragma once

#include <iostream>
#include <vector>
#include <glew.h>
#include <string>
#include <map>
#include <utility>

#include "shader\SkyboxShader.hpp"
#include "texture\SkyboxTexture.hpp"
#include "../math/math.hpp"

class Skybox
{
public:
	Skybox();

	void loadVAO();

	void render(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix, GLfloat pTime);
	void toggleRotation();

	void setVAO(GLuint pVAO);
	void setVBO(GLuint pVBO);

	GLuint getVBO() const;
	GLuint getVAO() const;

	void setCurrentCubeMapTexture(GLuint pCubeMapTexture);
	GLuint getCurrentCubeMapTexture() const;

	void changeSkyboxTexture(unsigned int pRandomSkymapTexture);
	void addTexturePack(std::string pPackFilePath);

private:
	// Skybox VertexArrayObject
	GLuint mSkyBoxVAO;
	// Skybox VertexBufferObject
	GLuint mSkyBoxVBO;
	// Cubemap texture ID
	GLuint mCurrentCubeMapTexture;
	// Cubemap vertices
	std::vector<GLfloat> mVertices;
	// Skybo Shader
	SkyboxShader* mShader;
	// Texture Packs
	std::vector<SkyboxTexture*> mTexturePacks;
	// Rotating skybox
	bool mIsRotating;
	// Current rotation
	GLfloat mRotation;

};