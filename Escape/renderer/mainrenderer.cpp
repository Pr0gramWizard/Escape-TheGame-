#include "mainrenderer.hpp"

const char* MainRenderer::ENTITY_VERTEX = "shaders/b.vert";
const char* MainRenderer::ENTITY_FRAGMENT = "shaders/a.frag";
const char* MainRenderer::TERRAIN_VERTEX = "shaders/terrain.vert";
const char* MainRenderer::TERRAIN_FRAGMENT = "shaders/terrain.frag";
const char* MainRenderer::TERRAIN_NORMAL_VERTEX = "shaders/terrain_normal.vert";
const char* MainRenderer::TERRAIN_NORMAL_FRAGMENT = "shaders/terrain_normal.frag";
const char* MainRenderer::TERRAIN_NORMAL_GEOMETRY = "shaders/terrain_normal.gs";
const char* MainRenderer::SKYBOX_VERTEX = "shaders/skybox.vert";
const char* MainRenderer::SKYBOX_FRAGMENT = "shaders/skybox.frag";
const char* MainRenderer::TEXT_VERTEX = "shaders/text.vert";
const char* MainRenderer::TEXT_FRAGMENT = "shaders/text.frag";
const char* MainRenderer::OBJECT_VERTEX = "shaders/object.vert";
const char* MainRenderer::OBJECT_FRAGMENT = "shaders/object.frag";


MainRenderer::MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer)
{
	EntityShader* entityshader = new EntityShader(ENTITY_VERTEX, ENTITY_FRAGMENT);
	mEntityRenderer = new EntityRenderer(entityshader,pProjectionMatrix);

	TerrainShader* terrainshader = new TerrainShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	TerrainShader* normalshader = new TerrainShader(TERRAIN_NORMAL_VERTEX, TERRAIN_NORMAL_FRAGMENT, TERRAIN_NORMAL_GEOMETRY);
	mTerrainRenderer = new TerrainRenderer(terrainshader, pProjectionMatrix);
	mNormalRenderer = new TerrainRenderer(normalshader, pProjectionMatrix);

	SkyboxShader* skyboxshader = new SkyboxShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	mSkyboxRenderer = new SkyboxRenderer(skyboxshader, pProjectionMatrix);

	TextShader* textshader = new TextShader(TEXT_VERTEX, TEXT_FRAGMENT);
	mTextRenderer = new TextRenderer(textshader);

	ObjectShader* objectshader = new ObjectShader(OBJECT_VERTEX, OBJECT_FRAGMENT);
	mObjectRenderer = new ObjectRenderer(objectshader,pProjectionMatrix);

	this->setDrawMode(0);

	mPlayer = pPlayer;

}

void MainRenderer::prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE)
{
	glClearColor(pRED, pGREEN, pBLUE, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainRenderer::render(glm::mat4 pViewMatrix, float pPlayerBelowLake, vector<Light*> pLights, glm::vec4 pClipPlane, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, bool pDiscoTime, float pFogDensity, float pFogGradient,float pDelta)
{
	this->prepare(pRED, pGREEN, pBLUE);
	glShadeModel(GL_SMOOTH);


	if (this->getDrawMode())
	{

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	for (Object &object : mObjects)
	{
		mObjectRenderer->startShader();
		mObjectRenderer->loadModelMatrix(&object);
		mObjectRenderer->loadViewMatrix(mPlayer->getViewMatrix());
		mObjectRenderer->loadClipPlane(pClipPlane);
		mObjectRenderer->loadLights(pLights, pDiscoTime);
		mObjectRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
		mObjectRenderer->loadFogData(pFogDensity, pFogGradient);
		mObjectRenderer->render(object);
		mObjectRenderer->stopShader();
	}



	// entities
	mEntityRenderer->startShader();
	mEntityRenderer->loadViewMatrix(pViewMatrix);
	mEntityRenderer->loadClipPlane(pClipPlane);
	mEntityRenderer->loadLights(pLights, pDiscoTime);
	mEntityRenderer->loadFogData(pFogDensity, pFogGradient);
	mEntityRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
	mEntityRenderer->render(mEntities);
	mEntityRenderer->render(mSpecial, LINES);
	mEntityRenderer->stopShader();



	
	// terrain
	mTerrainRenderer->startShader();
	mTerrainRenderer->loadViewMatrix(pViewMatrix);
	mTerrainRenderer->loadClipPlane(pClipPlane);
	mTerrainRenderer->loadLights(pLights, pDiscoTime);
	mTerrainRenderer->loadDepthCubemapTexture(pLights);
	mTerrainRenderer->loadFogData(pFogDensity, pFogGradient);
	mTerrainRenderer->loadPlayerBelowLake(pPlayerBelowLake);
	mTerrainRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);

	
	mNormalRenderer->startShader();
	mNormalRenderer->loadViewMatrix(pViewMatrix);
	mNormalRenderer->loadPlayerBelowLake(pPlayerBelowLake);
	mNormalRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
	
	for (Terrain &terrain : mTerrains)
	{
		if (terrain.getName() == "Decke") {
			glCullFace(GL_FRONT);
			mTerrainRenderer->loadTexture(terrain);
			mTerrainRenderer->render(terrain);
			if (this->getNormalMode())
			{
				mNormalRenderer->render(terrain);
			}
			glCullFace(GL_BACK);
		}
		else {
			mTerrainRenderer->loadTexture(terrain);
			mTerrainRenderer->render(terrain);
			if (this->getNormalMode())
			{
				mNormalRenderer->render(terrain);
			}
		}
	}


}

void MainRenderer::setFPS(int pFPS)
{
	mFPS = pFPS;
}

void MainRenderer::renderDebugInformation()
{
	if (this->getDebugMode())
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
		std::string FPS = "FPS: " + std::to_string(this->mFPS);
		std::string PlayerMovementSpeed = "Movementspeed: " + std::to_string(mPlayer->getMovementSpeed());
		std::string PlayerCrouch = "Crouching: ";
		std::string PlayerSprint = "Sprinting: ";
		std::string PlayerJump = "Jumping: ";

		if (mPlayer->getCrouching())
		{
			PlayerCrouch += "True";
		}
		else
		{
			PlayerCrouch += "False";
		}

		if (Keyboard::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			PlayerSprint += "True";
		}
		else
		{
			PlayerSprint += "False";
		}

		if (mPlayer->getJumping())
		{
			PlayerJump += "True";
		}
		else
		{
			PlayerJump += "False";
		}

	

		mTextRenderer->RenderText(PlayerName.c_str(), 20.0f, 1000.0f, 0.4f, glm::vec3(1, 1, 1));
		mTextRenderer->RenderText(FPS.c_str(), 20.0f, 980.0f, 0.4f, glm::vec3(1, 1, 1));
		mTextRenderer->RenderText(PlayerPosition.c_str() , 20.0f, 960.0f, 0.4f, glm::vec3(1, 1, 1));
		mTextRenderer->RenderText(PlayerMovementSpeed.c_str(), 20.0f, 940.0f, 0.4f, glm::vec3(1, 1, 1));
		mTextRenderer->RenderText(PlayerCrouch.c_str(), 20.0f, 920.0f, 0.4f, glm::vec3(1, 1, 1));
		mTextRenderer->RenderText(PlayerSprint.c_str(), 20.0f, 900.0f, 0.4f, glm::vec3(1, 1, 1));
		mTextRenderer->RenderText(PlayerJump.c_str(), 20.0f, 880.0f, 0.4f, glm::vec3(1, 1, 1));
		
	}
	
}

void MainRenderer::addToList(Entity &pEntity)
{
	mEntities.push_back(pEntity);
}

void MainRenderer::addToList(Object &pObject)
{
	mObjects.push_back(pObject);
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

void MainRenderer::setNormalMode(bool pMode)
{
	normalMode = pMode;
}

bool MainRenderer::getNormalMode() const
{
	return normalMode;
}

void MainRenderer::setDebugMode(bool pMode)
{
	debugMode = pMode;
}

bool MainRenderer::getDebugMode() const
{
	return debugMode;
}

void MainRenderer::addToList(Terrain &pTerrain)
{
	mTerrains.push_back(pTerrain);
}

void MainRenderer::addToList(Terrain* pTerrain)
{
	mTerrainsP.push_back(pTerrain);
}

void MainRenderer::clearLists()
{
	mEntities.clear();
	mTerrains.clear();
	mSpecial.clear();
	mRenderMode.clear();
	mTerrainsP.clear();
}

void MainRenderer::renderSceneForDepthCubeMap(ShadowShader *shadowshader)
{
	glClear(GL_DEPTH_BUFFER_BIT);

	// shader is the shadow shader -> only needs model matrix

	// only terrains cast shadows yet

	/*for (Object &object : mObjects)
	{
		mObjectRenderer->loadModelMatrix(&object);
		mObjectRenderer->render(object);
	}



	// entities
	mEntityRenderer->startShader();
	mEntityRenderer->render(mEntities);*/

	// terrain

	for (Terrain &terrain : mTerrains)
	{
		shadowshader->loadModelMatrix(terrain.getModelMatrix());
		glDrawElements(GL_TRIANGLES, terrain.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	}
}

void MainRenderer::cleanUp()
{
	//mEntityRenderer->cleanUp();
	//mTerrainRenderer->cleanUp();
}
