#include "lakeRenderer.hpp"

// constructor
LakeRenderer::LakeRenderer(LakeShader * pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

// destructor
LakeRenderer::~LakeRenderer()
{
}

// renders a single Lake
void LakeRenderer::render(Lake &pLake)
{
	prepareLake(&pLake);
	loadModelMatrix(&pLake);
	glDrawElements(GL_TRIANGLES, pLake.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	unbindLake();
}


// binds the vertex array and the needed attributes for the Lake
void LakeRenderer::prepareLake(Lake pLake)
{
	Model* model = pLake.getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here

	// end texturepart
}

// prepares the renderer for rendering
void LakeRenderer::prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// binds the vertex array and the needed attributes for the Lake
void LakeRenderer::prepareLake(Lake* pLake)
{
	Model* model = pLake->getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here

	// end texturepart
}

// disables the vertex array and the used attibutes
void LakeRenderer::unbindLake()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

// loads the model matrix for a Lake
void LakeRenderer::loadModelMatrix(Lake pLake)
{
	mShader->loadModelMatrix(pLake.getModelMatrix());
}

// loads the model matrix for a Lake
void LakeRenderer::loadModelMatrix(Lake* pLake)
{
	mShader->loadModelMatrix(pLake->getModelMatrix());
}

void LakeRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void LakeRenderer::loadLights(vector<Light*> pLights)
{
	mShader->loadLights(pLights);
}

void LakeRenderer::startShader()
{
	mShader->use();
}

void LakeRenderer::stopShader()
{
	mShader->unuse();
}



