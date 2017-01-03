#include "entityRenderer.hpp"

// constructor
EntityRenderer::EntityRenderer(EntityShader* pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}


// destructor
EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::render(list<Entity> pEntities)
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

void EntityRenderer::render(Entity & pEntity)
{
	prepareEntity(&pEntity);
	loadModelMatrix(&pEntity);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	unbindEntity();
}

void EntityRenderer::prepareEntity(Entity pEntity)
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

void EntityRenderer::prepareEntity(Entity * pEntity)
{
	Model* model = pEntity->getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model->getTextureID());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "ourTexture"), 0);
	// end texturepart
}

void EntityRenderer::unbindEntity()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::loadModelMatrix(Entity pEntity)
{
	mShader->loadModelMatrix(pEntity.getModelMatrix());
}

void EntityRenderer::loadModelMatrix(Entity * pEntity)
{
	mShader->loadModelMatrix(pEntity->getModelMatrix());
}

void EntityRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void EntityRenderer::loadLight(Light *pLight)
{
	mShader->loadLight(pLight);
}

void EntityRenderer::startShader()
{
	mShader->use();
}

void EntityRenderer::stopShader()
{
	mShader->unuse();
}

void EntityRenderer::render(std::list<Entity> pEntities, RenderMode pMode)
{
	for (Entity &pEntity : pEntities)
	{
		prepareEntity(pEntity);
		loadModelMatrix(pEntity);
		switch (pMode)
		{
		case RenderMode::POINTS:
			glDrawElements(GL_POINTS, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
			break;
		case RenderMode::LINES:
			glDrawElements(GL_LINES, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
			break;
		case RenderMode::LINE_STRIP:
			glDrawElements(GL_LINE_STRIP, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
			break;
		case RenderMode::LINE_LOOP:
			glDrawElements(GL_LINE_LOOP, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
			break;
		case RenderMode::TRIANGLES:
			glDrawElements(GL_TRIANGLES, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
			break;
		case RenderMode::TRIANGLE_STRIP:
			glDrawElements(GL_TRIANGLE_STRIP, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
			break;
		case RenderMode::TRIANGLE_FAN:
			glDrawElements(GL_TRIANGLE_FAN, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
			break;
		}
		unbindEntity();
	}

}