#pragma once

#include <iostream>
#include <vector>
#include <glew.h>
#include <SOIL.h>

#include "shader\SkyboxShader.hpp"


class Skybox
{
public:
	Skybox();

	void addTexture(const char* pTextureLocation);

	void loadVAO();

	void render(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix);

	void setVAO(GLuint pVAO);
	GLuint getVAO() const;

	void setVBO(GLuint pVBO);
	GLuint getVBO() const;

	void setCubeMapTexture(GLuint pCubeMapTexture);
	GLuint getCubeMapTexture() const;

	GLuint loadTexture();

private:

	GLuint mSkyBoxVAO;
	GLuint mSkyBoxVBO;

	GLuint mCubeMapTexture;

	std::vector<GLfloat> mVertices;
	std::vector<const GLchar*> mFaces;

	SkyboxShader* mShader;

};
