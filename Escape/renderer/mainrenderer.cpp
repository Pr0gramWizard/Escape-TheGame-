#include "mainrenderer.hpp"

const char* MainRenderer::ENTITY_VERTEX = "shaders/b.vert";
const char* MainRenderer::ENTITY_FRAGMENT = "shaders/a.frag";
const char* MainRenderer::TERRAIN_VERTEX = "shaders/terrain.vert";
const char* MainRenderer::TERRAIN_FRAGMENT = "shaders/terrain.frag";

MainRenderer::MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer)
{
	EntityShader* entityshader = new EntityShader(ENTITY_VERTEX, ENTITY_FRAGMENT);
	mEntityRenderer = new EntityRenderer(entityshader,pProjectionMatrix);

	TerrainShader* terrainshader = new TerrainShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	mTerrainRenderer = new TerrainRenderer(terrainshader, pProjectionMatrix);

	this->setDrawMode(0);

	mPlayer = pPlayer;

}

MainRenderer::~MainRenderer()
{
}

void MainRenderer::prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE)
{
	glClearColor(pRED, pGREEN, pBLUE, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainRenderer::render(glm::mat4 pViewMatrix, vector<Light*> pLights, glm::vec4 pClipPlane, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE)
{
	this->prepare(pRED, pGREEN, pBLUE);
	glShadeModel(GL_SMOOTH);

	// entities
	mEntityRenderer->startShader();
	mEntityRenderer->loadViewMatrix(pViewMatrix);
	mEntityRenderer->loadClipPlane(pClipPlane);
	mEntityRenderer->loadLights(pLights);
	mEntityRenderer->loadFogData(0.01f, 2.0f);
	mEntityRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mEntityRenderer->render(mEntities);
	mEntityRenderer->render(mSpecial, LINES);
	mEntityRenderer->stopShader();

	// terrain
	mTerrainRenderer->startShader();
	mTerrainRenderer->loadViewMatrix(pViewMatrix);
	mTerrainRenderer->loadClipPlane(pClipPlane);
	mTerrainRenderer->loadLights(pLights);
	mTerrainRenderer->loadFogData(0.01f, 2.0f);
	mTerrainRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
	if (this->getDrawMode())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	for (Terrain &terrain : mTerrains)
	{
		mTerrainRenderer->render(terrain);
	}
	mTerrainRenderer->stopShader();
}

void MainRenderer::addToList(Entity &pEntity)
{
	mEntities.push_back(pEntity);
}

void MainRenderer::addToList(Entity &pEntity, RenderMode pMode)
{
	mSpecial.push_back(pEntity);
	mRenderMode.push_back(pMode);
}

void MainRenderer::setDrawMode(bool pMode)
{
	drawMode = pMode;
}

bool MainRenderer::getDrawMode() const
{
	return drawMode;
}

void MainRenderer::addToList(Terrain &pTerrain)
{
	mTerrains.push_back(pTerrain);
}

void MainRenderer::clearLists()
{
	mEntities.clear();
	mTerrains.clear();
	mSpecial.clear();
	mRenderMode.clear();
}

void MainRenderer::cleanUp()
{
	//mEntityRenderer->cleanUp();
	//mTerrainRenderer->cleanUp();
}
