#include "terrainRenderer.hpp"
// constructor
TerrainRenderer::TerrainRenderer(TerrainShader * pShader, glm::mat4 pProjectionMatrix)
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		unbindTerrain();
	}
}

// renders a single terrain
void TerrainRenderer::render(Terrain &pTerrain)
{
	prepareTerrain(&pTerrain);
	loadModelMatrix(&pTerrain);
	glDrawElements(GL_TRIANGLES, pTerrain.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	unbindTerrain();
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

// prepares the renderer for rendering
void TerrainRenderer::prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void TerrainRenderer::loadLight(Light *pLight)
{
	mShader->loadLight(pLight);
}

void TerrainRenderer::startShader()
{
	mShader->use();
}

void TerrainRenderer::stopShader()
{
	mShader->unuse();
}


