#include "terrainRenderer.hpp"
// constructor
TerrainRenderer::TerrainRenderer(TerrainShader * pShader,glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

// destructor
TerrainRenderer::~TerrainRenderer()
{
}

// renders every terrain in pTerrains
void TerrainRenderer::render(list<Terrain> pTerrains)
{
	for (Terrain terrain : pTerrains)
	{
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		unbindTerrain();
	}
}

// renders a single terrain
void TerrainRenderer::render(Terrain &pTerrain)
{
	prepareTerrain(&pTerrain);
	loadModelMatrix(&pTerrain);

	mShader->use();
	glDrawElements(GL_TRIANGLES, pTerrain.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);

	unbindTerrain();
}

// renders a single terrain
void TerrainRenderer::render(Terrain* pTerrain)
{
	prepareTerrain(pTerrain);
	loadModelMatrix(pTerrain);

	mShader->use();
	glDrawElements(GL_TRIANGLES, pTerrain->getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);

	unbindTerrain();
}

void TerrainRenderer::loadTexture(Terrain &pTerrain)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pTerrain.getGrasTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "grass"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pTerrain.getStoneTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "stone"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, pTerrain.getFlowerTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "flower"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, pTerrain.getMudTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "mud"), 3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, pTerrain.getBlendMapTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "blendMap"), 4);
}

void TerrainRenderer::loadTexture(Terrain* pTerrain)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pTerrain->getGrasTexture());
	glUniform1i(glGetUniformLocation(mShader->getProgramID(), "texture"), 0);
}

void TerrainRenderer::loadDepthCubemapTexture(vector<Light*> pLights)
{
	for (unsigned int i = 0; i < MAX_LIGHTS; ++i) {
		if (i < pLights.size()) {
			glActiveTexture(GL_TEXTURE5 + i);
			glBindTexture(GL_TEXTURE_CUBE_MAP, pLights[i]->getDepthCubemap());
			glUniform1i(glGetUniformLocation(mShader->getProgramID(), "depthCubemap" + i), 5 + i);
		}
	}
}

GLuint TerrainRenderer::getProgramID() const
{
	return mShader->getProgramID();
}


// binds the vertex array and the needed attributes for the terrain
void TerrainRenderer::prepareTerrain(Terrain pTerrain)
{
	Model* model = pTerrain.getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here
	// end texturepart
}

// binds the vertex array and the needed attributes for the terrain
void TerrainRenderer::prepareTerrain(Terrain* pTerrain)
{
	Model* model = pTerrain->getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here

	// end texturepart
}

// disables the vertex array and the used attibutes
void TerrainRenderer::unbindTerrain()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

// loads the model matrix for a terrain
void TerrainRenderer::loadModelMatrix(Terrain pTerrain)
{
	mShader->loadModelMatrix(pTerrain.getModelMatrix());
}

// loads the model matrix for a terrain
void TerrainRenderer::loadModelMatrix(Terrain* pTerrain)
{
	mShader->loadModelMatrix(pTerrain->getModelMatrix());
}

void TerrainRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void TerrainRenderer::loadLights(vector<Light*> pLights, bool pDiscoTime)
{
	mShader->loadLights(pLights, pDiscoTime);
}

void TerrainRenderer::loadClipPlane(glm::vec4 pClipPlane)
{
	mShader->loadPlane(pClipPlane);
}

void TerrainRenderer::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	mShader->loadFogData(pDensity, pGradient);
}

void TerrainRenderer::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	mShader->loadBackgroundColor(pRed, pGreen, pBlue);
}

void TerrainRenderer::loadPlayerBelowLake(GLfloat pPlayerBelowLake)
{
	mShader->loadPlayerBelowLake(pPlayerBelowLake);
}

void TerrainRenderer::startShader()
{
	mShader->use();
}

void TerrainRenderer::stopShader()
{
	mShader->unuse();
}


