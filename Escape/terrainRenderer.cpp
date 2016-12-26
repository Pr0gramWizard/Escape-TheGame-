#include "terrainRenderer.hpp"

TerrainRenderer::TerrainRenderer(Testshader * pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::render(list<Terrain> pTerrains)
{
	for (Terrain terrain : pTerrains)
	{
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		unbindTerrain();
	}
}

void TerrainRenderer::render(Terrain pTerrain)
{
	prepareTerrain(pTerrain);
	loadModelMatrix(pTerrain);
	glDrawElements(GL_TRIANGLES, pTerrain.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	unbindTerrain();
}

void TerrainRenderer::render(Terrain* pTerrain)
{
	prepareTerrain(pTerrain);
	loadModelMatrix(pTerrain);
	glDrawElements(GL_TRIANGLES, pTerrain->getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	unbindTerrain();
}

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

void TerrainRenderer::prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

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
void TerrainRenderer::unbindTerrain()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain pTerrain)
{
	mShader->loadModelMatrix(pTerrain.getModelMatrix());
}

void TerrainRenderer::loadModelMatrix(Terrain* pTerrain)
{
	mShader->loadModelMatrix(pTerrain->getModelMatrix());
}

