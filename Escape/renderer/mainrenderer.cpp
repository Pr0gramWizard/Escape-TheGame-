#include "mainrenderer.hpp"

const char* MainRenderer::ENTITY_VERTEX = "shaders/b.vert";
const char* MainRenderer::ENTITY_FRAGMENT = "shaders/a.frag";
const char* MainRenderer::TERRAIN_VERTEX = "shaders/terrain.vert";
const char* MainRenderer::TERRAIN_FRAGMENT = "shaders/terrain.frag";
const char* MainRenderer::SKYBOX_VERTEX = "shaders/skybox.vert";
const char* MainRenderer::SKYBOX_FRAGMENT = "shaders/skybox.frag";
const char* MainRenderer::TEXT_VERTEX = "shaders/text.vert";
const char* MainRenderer::TEXT_FRAGMENT = "shaders/text.frag";

MainRenderer::MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer)
{
	EntityShader* entityshader = new EntityShader(ENTITY_VERTEX, ENTITY_FRAGMENT);
	mEntityRenderer = new EntityRenderer(entityshader,pProjectionMatrix);

	TerrainShader* terrainshader = new TerrainShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	mTerrainRenderer = new TerrainRenderer(terrainshader, pProjectionMatrix);

	SkyboxShader* skyboxshader = new SkyboxShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	mSkyboxRenderer = new SkyboxRenderer(skyboxshader, pProjectionMatrix);

	TextShader* textshader = new TextShader(TEXT_VERTEX, TEXT_FRAGMENT);
	mTextRenderer = new TextRenderer(textshader);

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


	/*
	mSkyboxRenderer->startShader();
	mSkyboxRenderer->loadViewMatrix(pViewMatrix);
	mSkyboxRenderer->render(mSkybox);
	mSkyboxRenderer->stopShader();
	*/


}

void MainRenderer::renderDebugInformation()
{
	if (this->getDrawMode())
	{
		glEnable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::string PlayerPosition = "Player Position: ";
		float XPos = mPlayer->getPosition().x;
		float YPos = mPlayer->getPosition().y;
		float ZPos = mPlayer->getPosition().z;

		PlayerPosition = PlayerPosition + std::to_string(XPos) + "," + std::to_string(YPos) + "," + std::to_string(ZPos);

		std::string PlayerName = "Name: " + (std::string)mPlayer->getName();
		std::string PlayerMovementSpeed = "Movementspeed: " + std::to_string(mPlayer->getMovementSpeed());



		mTextRenderer->RenderText(PlayerName.c_str(), 10.0f, 1000.0f, 0.4f, glm::vec3(1, 1, 1));
		mTextRenderer->RenderText(PlayerPosition.c_str() , 10.0f, 980.0f, 0.4f, glm::vec3(1, 1, 1));
		mTextRenderer->RenderText(PlayerMovementSpeed.c_str(), 10.0f, 960.0f, 0.4f, glm::vec3(1, 1, 1));
		
	}
	
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

void MainRenderer::addToList(Skybox* Skybox)
{
	mSkybox = Skybox;
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
