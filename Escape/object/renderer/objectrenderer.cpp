#include "objectrenderer.hpp"

// constructor
ObjectRenderer::ObjectRenderer(ObjectShader* pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

void ObjectRenderer::render(Object &pObject)
{
}

void ObjectRenderer::loadModelMatrix(Object pObject)
{
	mShader->loadModelMatrix(pObject.getModelMatrix());
}

void ObjectRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void ObjectRenderer::startShader()
{
	mShader->use();
}

void ObjectRenderer::stopShader()
{
	mShader->unuse();
}
