#include "mainrenderer.hpp"

// Shader locations
const char* MainRenderer::TERRAIN_VERTEX = "shaders/terrain.vert";
const char* MainRenderer::TERRAIN_FRAGMENT = "shaders/terrain.frag";
const char* MainRenderer::GUI_VERTEX = "shaders/gui.vert";
const char* MainRenderer::GUI_FRAGMENT = "shaders/gui.frag";


MainRenderer::MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer)
{
	// Creating terrain Shader
	TerrainShader* terrainshader = new TerrainShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	// Creating terrain renderer
	mTerrainRenderer = new TerrainRenderer(terrainshader, pProjectionMatrix);

	// Setting draw mode to normal
	this->setDrawMode(0);

	// Setting player instance
	mPlayer = pPlayer;

}

// Clearing whole screen with given color
void MainRenderer::prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE)
{
	glClearColor(pRED, pGREEN, pBLUE, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainRenderer::render(glm::mat4 pViewMatrix, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, float pDelta){

	// Preparing the scree
	this->prepare(pRED, pGREEN, pBLUE);

	mSkybox->render(pViewMatrix, mPlayer->getProjectionMatrix(),pDelta);

	// Polygon Mode
	if (this->getDrawMode())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	// Normal Mode
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Prepare terrain
	mTerrainRenderer->startShader();
	mTerrainRenderer->loadViewMatrix(pViewMatrix);
	mTerrainRenderer->loadLights(pLights, false);
	mTerrainRenderer->loadDepthCubemapTexture(pLights);
	mTerrainRenderer->loadPlayerBelowLake(false);
	mTerrainRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);

	// Render Terrain
	for (Terrain &terrain : mTerrains)
	{
		mTerrainRenderer->loadTexture(terrain);
		mTerrainRenderer->render(terrain);
	}
}

void MainRenderer::addToList(Skybox* pSkybox) {
	mSkybox = pSkybox;
}

// Add terrain to the render list
void MainRenderer::addToList(Terrain &pTerrain){
	mTerrains.push_back(pTerrain);
}

// Setting Draw Mode 
void MainRenderer::setDrawMode(bool pMode){
	drawMode = pMode;
}
// Returns the Draw Mode
bool MainRenderer::getDrawMode() const
{
	return drawMode;
}

// Clears the whole list
void MainRenderer::clearLists(){
	mTerrains.clear();
}

// Clear the list of terrains
void MainRenderer::clearTerrainList(){
	mTerrains.clear();
}
