#include "mainrenderer.hpp"

const char* MainRenderer::ENTITY_VERTEX = "shaders/b.vert";
const char* MainRenderer::ENTITY_FRAGMENT = "shaders/a.frag";
const char* MainRenderer::TERRAIN_VERTEX = "shaders/terrain.vert";
const char* MainRenderer::TERRAIN_FRAGMENT = "shaders/terrain.frag";

MainRenderer::MainRenderer(glm::mat4 pProjectionMatrix)
{
	EntityShader* entityshader = new EntityShader(ENTITY_VERTEX, ENTITY_FRAGMENT);
	mEntityRenderer = new EntityRenderer(entityshader,pProjectionMatrix);

	TerrainShader* terrainshader = new TerrainShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	mTerrainRenderer = new TerrainRenderer(terrainshader, pProjectionMatrix);
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
	glShadeModel(GL_SMOOTH);
	// entities
	mEntityRenderer->startShader();
	mEntityRenderer->loadViewMatrix(pViewMatrix);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mEntityRenderer->render(mEntities);
	mEntityRenderer->render(mSpecial, LINES);
	mEntityRenderer->stopShader();

	// terrain
	//Light* sun = new Light(glm::vec3(250, 1, 250), glm::vec3(1, 1, 0), glm::vec3(1, 0.01, 0.002));
	Light* sun = new Light(glm::vec3(0, 20, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	Light* sun2 = new Light(glm::vec3(500, 20, 0), glm::vec3(10.0f, 0.0f, 0.0f));
	Light* sun3 = new Light(glm::vec3(0, 20, 500), glm::vec3(0.0f, 0.0f, 10.0f));
	Light* sun4 = new Light(glm::vec3(500, 20, 500), glm::vec3(0.0f, 10.0f, 0.0f));
	vector<Light*> lights;
	lights.push_back(sun);
	lights.push_back(sun2);
	lights.push_back(sun3);
	lights.push_back(sun4);
	mTerrainRenderer->startShader();
	mTerrainRenderer->loadViewMatrix(pViewMatrix);
	mTerrainRenderer->loadLights(lights);
	for (Terrain &terrain : mTerrains)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
