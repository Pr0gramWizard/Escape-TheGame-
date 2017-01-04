#include "objectrenderer.hpp"

// constructor
ObjectRenderer::ObjectRenderer(ObjectShader* pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

void ObjectRenderer::render(Object & pObject)
{

}

void ObjectRenderer::loadModelMatrix(Object pEntity)
{
	// mShader->loadModelMatrix(pEntity.getModelMatrix());
}

void ObjectRenderer::startShader()
{
	mShader->use();
}

void ObjectRenderer::stopShader()
{
	mShader->unuse();
}
