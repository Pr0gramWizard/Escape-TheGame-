#include "skyboxrenderer.hpp"

// constructor
SkyboxRenderer::SkyboxRenderer(SkyboxShader* pSkybox, glm::mat4 pProjectionMatrix)
{
	mShader = pSkybox;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}


// destructor
SkyboxRenderer::~SkyboxRenderer()
{
}


void SkyboxRenderer::render(Skybox* pSkybox)
{
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	mShader->use();
	glBindVertexArray(pSkybox->getVAO());
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, pSkybox->getCubeMapTexture());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // Set dep
}


void SkyboxRenderer::prepareSkybox(Skybox* pSkybox)
{
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	mShader->use();
	glBindVertexArray(pSkybox->getVAO());
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, pSkybox->getCubeMapTexture());
}

void SkyboxRenderer::unbindSkybox()
{
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // Set dep
}



void SkyboxRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}


void SkyboxRenderer::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	mShader->loadBackgroundColor(pRed, pGreen, pBlue);
}

void SkyboxRenderer::startShader()
{
	mShader->use();
}

void SkyboxRenderer::stopShader()
{
	mShader->unuse();
}
