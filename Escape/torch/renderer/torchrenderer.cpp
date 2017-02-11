#include "Torchrenderer.hpp"

// constructor
TorchRenderer::TorchRenderer(TorchShader* pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

void TorchRenderer::render(Torch &pTorch)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pTorch.getTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "texture"), 0);
	pTorch.Draw(mShader);
}

void TorchRenderer::render(Torch* pTorch)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pTorch->getTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "texture"), 0);
	pTorch->Draw(mShader);
}


void TorchRenderer::loadModelMatrix(Torch* pTorch)
{
	mShader->loadModelMatrix(pTorch->getModelMatrix());
}

void TorchRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void TorchRenderer::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	mShader->loadFogData(pDensity, pGradient);
}

void TorchRenderer::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	mShader->loadBackgroundColor(pRed, pGreen, pBlue);
}

void TorchRenderer::loadClipPlane(glm::vec4 pClipPlane)
{
	mShader->loadPlane(pClipPlane);
}

void TorchRenderer::loadLights(vector<Light*> pLights, bool pDiscoTime)
{
	mShader->loadLights(pLights, pDiscoTime);
}

void TorchRenderer::startShader()
{
	mShader->use();
}

void TorchRenderer::stopShader()
{
	mShader->unuse();
}
