#include "objectrenderer.hpp"

// constructor
ObjectRenderer::EntityRenderer(EntityShader* pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}


// destructor
ObjectRenderer::~ObjectRenderer()
{
}

void ObjectRenderer::render(list<Entity> pEntities)
{
	for (Entity &entity : pEntities)
	{
		prepareEntity(entity);
		loadModelMatrix(entity);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, entity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		unbindEntity();
	}
}

void ObjectRenderer::render(Entity & pEntity)
{
	prepareEntity(&pEntity);
	loadModelMatrix(&pEntity);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	unbindEntity();
}

void ObjectRenderer::prepareEntity(Entity pEntity)
{
	Model* model = pEntity.getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texture Part
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model->getTextureID());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "ourTexture"), 0);

}

void ObjectRenderer::loadModelMatrix(Entity pEntity)
{
	mShader->loadModelMatrix(pEntity.getModelMatrix());
}

void ObjectRenderer::loadModelMatrix(Entity * pEntity)
{
	mShader->loadModelMatrix(pEntity->getModelMatrix());
}

void ObjectRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void ObjectRenderer::loadLight(Light *pLight)
{
	mShader->loadLight(pLight);
}

void ObjectRenderer::loadClipPlane(glm::vec4 pClipPlane)
{
	mShader->loadPlane(pClipPlane);
}

void ObjectRenderer::startShader()
{
	mShader->use();
}

void ObjectRenderer::stopShader()
{
	mShader->unuse();
}

void ObjectRenderer::render(std::list<Entity> pEntities, RenderMode pMode)
{	
	unbindEntity();
}