#include "skybox.hpp"

Skybox::Skybox()
{
	// Create 6 sided cube
	mVertices = {
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	for (unsigned int i = 0; i < mVertices.size(); ++i)
	{
		mVertices.at(i) = mVertices.at(i) * 1000;
	}

	// Create new shader
	mShader = new SkyboxShader("shaders/skybox.vert", "shaders/skybox.frag");

	// Create VAO
	this->loadVAO();
}

void Skybox::changeSkyboxTexture(unsigned int pRandomSkymapTexture) {
	// Prevent accessing an elment out of bound
	unsigned int arrayPosition = pRandomSkymapTexture % mTexturePacks.size();
	// Chaning the cube map texture
	setCurrentCubeMapTexture(mTexturePacks.at(arrayPosition)->getTextureID());
}

void Skybox::addTexturePack(std::string pPackFilePath) {
	SkyboxTexture* newTexture = new SkyboxTexture(pPackFilePath);
	mTexturePacks.push_back(newTexture);
	setCurrentCubeMapTexture(newTexture->getTextureID());
}

void Skybox::loadVAO()
{
	glGenVertexArrays(1, &mSkyBoxVAO);
	glGenBuffers(1, &mSkyBoxVBO);
	glBindVertexArray(mSkyBoxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mSkyBoxVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(GLfloat), &mVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	setVAO(mSkyBoxVAO);
	setVBO(mSkyBoxVBO);

}

void Skybox::render(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix)
{
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	mShader->use();
	mShader->loadViewMatrix(pViewMatrix);
	mShader->loadProjectionMatrix(pProjectionMatrix);
	// skybox cube
	glBindVertexArray(this->getVAO());
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->getCurrentCubeMapTexture());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // Set dep
}

void Skybox::setVAO(GLuint pVAO)
{
	this->mSkyBoxVAO = pVAO;
}

GLuint Skybox::getVAO() const
{
	return mSkyBoxVAO;
}

void Skybox::setVBO(GLuint pVBO)
{
	this->mSkyBoxVBO = pVBO;
}

GLuint Skybox::getVBO() const
{
	return mSkyBoxVBO;
}

void Skybox::setCurrentCubeMapTexture(GLuint pCubeMapTexture)
{
	mCurrentCubeMapTexture = pCubeMapTexture;
}

GLuint Skybox::getCurrentCubeMapTexture() const
{
	return mCurrentCubeMapTexture;
}

