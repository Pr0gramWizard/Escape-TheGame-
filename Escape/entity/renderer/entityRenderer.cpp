#include "entityRenderer.hpp"

// Constructor
EntityRenderer::EntityRenderer(EntityShader* pShader, glm::mat4 pProjectionMatrix)
{
	// Setting up the shader
	mShader = pShader;

	// Loading Projections Matrix into the shader
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

// Destructor
EntityRenderer::~EntityRenderer()
{
	delete mShader;
}

// Render methods:

// Render Entites with a given list
void EntityRenderer::render(std::list<Entity> pEntities)
{
	// Looping through the list
	for (Entity &entity : pEntities)
	{
		// Call render function
		this->render(entity);
	}
}

// Render Entites with a given list and given RenderMode
void EntityRenderer::render(std::list<Entity> pEntities, RenderMode pMode)
{
	// Looping through the list
	for (Entity &pEntity : pEntities)
	{
		// Call render function
		this->render(pEntity, pMode);
	}
}

// Render Entites with a given object
void EntityRenderer::render(Entity& pEntity)
{
	// Prepare the entity
	prepareEntity(pEntity);
	// Load its model matrix
	loadModelMatrix(pEntity);
	// Render the object with full polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Draw the object
	glDrawElements(GL_TRIANGLES, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	// Unbind entity
	unbindEntity();
}

// Render Entites with a given object and render mode
void EntityRenderer::render(Entity& pEntity, RenderMode pMode)
{
	// Prepare the entity
	prepareEntity(pEntity);
	// Load its model matrix
	loadModelMatrix(pEntity);
	// Render the object with full polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Switching through the Rendermodes to find the right one
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
	// Unbinding the entity
	unbindEntity();
}

// Unbinding entites
void EntityRenderer::unbindEntity()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

// Preparing the entity (given as object)
void EntityRenderer::prepareEntity(Entity pEntity)
{
	// Get Model of the entity
	Model* model = pEntity.getModel();
	// Binding the Vertex Array
	glBindVertexArray(model->getVaoId());
	// Enable attributes (position, normals, textures)
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

// Preparing the entity (given as pointer to object)
void EntityRenderer::prepareEntity(Entity * pEntity)
{
	// Get Model of the entity
	Model* model = pEntity->getModel();
	// Binding the Vertex Array
	glBindVertexArray(model->getVaoId());
	// Enable attributes (position, normals, textures)
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}


// Load Model Matrix (given object)
void EntityRenderer::loadModelMatrix(Entity pEntity)
{
	mShader->loadModelMatrix(pEntity.getModelMatrix());
}

// Load Model Matrix (given pointer to object)
void EntityRenderer::loadModelMatrix(Entity* pEntity)
{
	mShader->loadModelMatrix(pEntity->getModelMatrix());
}

// Load View Matrix
void EntityRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

// Load list of lights
void EntityRenderer::loadLights(std::vector<Light*> pLights)
{
	mShader->loadLights(pLights);
}

// Load clipping plane
void EntityRenderer::loadClipPlane(glm::vec4 pClipPlane)
{
	mShader->loadPlane(pClipPlane);
}

// Load fog data
void EntityRenderer::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	mShader->loadFogData(pDensity, pGradient);
}

// Load Background color
void EntityRenderer::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	mShader->loadBackgroundColor(pRed, pGreen, pBlue);
}

// Start Entity Shader
void EntityRenderer::startShader()
{
	mShader->use();
}

// Stop Entity Shader
void EntityRenderer::stopShader()
{
	mShader->unuse();
}

