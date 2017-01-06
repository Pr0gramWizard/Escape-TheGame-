#include "lakeRenderer.hpp"

// constructor
LakeRenderer::LakeRenderer(LakeShader * pShader, glm::mat4 pProjectionMatrix, LakeFrameBuffers* pLakeFbos)
{
	mLakeFbos = pLakeFbos;
	mShader = pShader;
	mShader->use();
	mShader->connectTextureUnits();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	// use camera values instead!!
	mShader->loadNearFar(0.1f, 1000.0f);
	mShader->unuse();
}

// destructor
LakeRenderer::~LakeRenderer()
{
}

// renders a single Lake
void LakeRenderer::render(glm::mat4 pViewMatrix, Lake &pLake, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE)
{
	this->startShader();
	this->loadViewMatrix(pViewMatrix);
	this->loadLights(pLights);
	this->loadFogData(0.01f, 2.0f);
	this->loadBackgroundColor(pRED, pGREEN, pBLUE);
	prepareLake(&pLake);
	loadModelMatrix(&pLake);
	glDrawElements(GL_TRIANGLES, pLake.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	unbindLake();
	this->stopShader();
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
	// Texturepart here
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mLakeFbos->getReflactionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mLakeFbos->getRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mLakeFbos->getRefractionDepthTexture());
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// end texturepart
}

// disables the vertex array and the used attibutes
void LakeRenderer::unbindLake()
{
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
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

void LakeRenderer::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	mShader->loadFogData(pDensity, pGradient);
}

void LakeRenderer::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	mShader->loadBackgroundColor(pRed, pGreen, pBlue);
}

void LakeRenderer::loadNearFar(GLfloat pNear, GLfloat pFar)
{
	mShader->loadNearFar(pNear, pFar);
}

void LakeRenderer::startShader()
{
	mShader->use();
}

void LakeRenderer::stopShader()
{
	mShader->unuse();
}



