#include "mainrenderer.hpp"

const char* MainRenderer::ENTITY_VERTEX = "shaders/b.vert";
const char* MainRenderer::ENTITY_FRAGMENT = "shaders/a.frag";
const char* MainRenderer::TERRAIN_VERTEX = "shaders/terrain.vert";
const char* MainRenderer::TERRAIN_FRAGMENT = "shaders/terrain.frag";

MainRenderer::MainRenderer(glm::mat4 pProjectionMatrix)
{
	mEntityRenderer = new EntityRenderer();
	mEntityRenderer->addShader(ENTITY_VERTEX, ENTITY_FRAGMENT);

	Testshader* terrainShader = new Testshader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	terrainShader->bindAttribute(0, "position");
	terrainShader->bindAttribute(1, "normal");
	terrainShader->bindAttribute(2, "texCoord");
	mTerrainRenderer = new TerrainRenderer(terrainShader, pProjectionMatrix);
}

MainRenderer::~MainRenderer()
{
}

void MainRenderer::prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainRenderer::render(glm::mat4 pViewMatrix)
{
	mTerrainRenderer->loadViewMatrix(pViewMatrix);
	mTerrainRenderer->startShader();
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

void MainRenderer::addToList(Terrain &pTerrain)
{
	mTerrains.push_back(pTerrain);
}

void MainRenderer::clearLists()
{
	mEntities.clear();
	mTerrains.clear();
}

void MainRenderer::cleanUp()
{
	//mEntityRenderer->cleanUp();
	//mTerrainRenderer->cleanUp();
}
