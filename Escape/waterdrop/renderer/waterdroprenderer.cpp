#include "Waterdroprenderer.hpp"

// constructor
WaterdropRenderer::WaterdropRenderer(WaterdropShader* pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

void WaterdropRenderer::render(Waterdrop &pWaterdrop)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pWaterdrop.getTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "texture"), 0);
	pWaterdrop.Draw(mShader);
}

void WaterdropRenderer::loadModelMatrix(Waterdrop* pWaterdrop)
{
	mShader->loadModelMatrix(pWaterdrop->getModelMatrix());
}

void WaterdropRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void WaterdropRenderer::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	mShader->loadFogData(pDensity, pGradient);
}

void WaterdropRenderer::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	mShader->loadBackgroundColor(pRed, pGreen, pBlue);
}

void WaterdropRenderer::loadClipPlane(glm::vec4 pClipPlane)
{
	mShader->loadPlane(pClipPlane);
}

void WaterdropRenderer::loadLights(vector<Light*> pLights, bool pDiscoTime)
{
	mShader->loadLights(pLights, pDiscoTime);
}

void WaterdropRenderer::startShader()
{
	mShader->use();
}

void WaterdropRenderer::stopShader()
{
	mShader->unuse();
}
