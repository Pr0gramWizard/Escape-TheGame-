#include "mainrenderer.hpp"

// Shader locations
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
	// Creating Entity Shader
	EntityShader* entityshader = new EntityShader(ENTITY_VERTEX, ENTITY_FRAGMENT);
	// Creating Entity Renderer
	mEntityRenderer = new EntityRenderer(entityshader,pProjectionMatrix);

	// Creating terrain Shader
	TerrainShader* terrainshader = new TerrainShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	// Creating Geometry Shader for the normal vectors (not used)
	TerrainShader* normalshader = new TerrainShader(TERRAIN_NORMAL_VERTEX, TERRAIN_NORMAL_FRAGMENT, TERRAIN_NORMAL_GEOMETRY);
	// Creating terrain renderer
	mTerrainRenderer = new TerrainRenderer(terrainshader, pProjectionMatrix);
	// Creating normal renderer
	mNormalRenderer = new TerrainRenderer(normalshader, pProjectionMatrix);

	// Creating Text Shader
	TextShader* textshader = new TextShader(TEXT_VERTEX, TEXT_FRAGMENT);
	// Creating Text Renderer
	mTextRenderer = new TextRenderer(textshader);

	// Creating Object Shader (used for Stones)
	ObjectShader* objectshader = new ObjectShader(OBJECT_VERTEX, OBJECT_FRAGMENT);
	// Creating Object Renderer
	mObjectRenderer = new ObjectRenderer(objectshader,pProjectionMatrix);

	// Creating waterdrop shader
	WaterdropShader* watershader = new WaterdropShader(OBJECT_VERTEX, OBJECT_FRAGMENT);
	// Creating waterdrop renderer
	mWaterRenderer = new WaterdropRenderer(watershader, pProjectionMatrix);

	// Creating torch shader
	TorchShader* torchshader = new TorchShader(OBJECT_VERTEX, OBJECT_FRAGMENT);
	// Creating torch renderer
	mTorchRenderer = new TorchRenderer(torchshader, pProjectionMatrix);

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

void MainRenderer::render(glm::mat4 pViewMatrix, float pPlayerBelowLake, vector<Light*> pLights, glm::vec4 pClipPlane, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, bool pDiscoTime, float pFogDensity, float pFogGradient,float pDelta)
{
	// Preparing the scree
	this->prepare(pRED, pGREEN, pBLUE);

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

	// Render all objects
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

	// Render all Waterdrops
	for (Waterdrop &object : mWaterDrop)
	{
		mWaterRenderer->startShader();
		if (object.getPosition().y <= 3.0f)
		{
			object.mStatus = true;
		}
		else
		{
			object.mStatus = false;
		}
		mWaterRenderer->loadModelMatrix(&object);
		mWaterRenderer->loadViewMatrix(mPlayer->getViewMatrix());
		mWaterRenderer->loadClipPlane(pClipPlane);
		mWaterRenderer->loadLights(pLights, pDiscoTime);
		mWaterRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
		mWaterRenderer->loadFogData(pFogDensity, pFogGradient);
		mWaterRenderer->render(object);
		mWaterRenderer->stopShader();
	}


	// Prepare terrain
	mTerrainRenderer->startShader();
	mTerrainRenderer->loadViewMatrix(pViewMatrix);
	mTerrainRenderer->loadClipPlane(pClipPlane);
	mTerrainRenderer->loadLights(pLights, pDiscoTime);
	mTerrainRenderer->loadDepthCubemapTexture(pLights);
	mTerrainRenderer->loadFogData(pFogDensity, pFogGradient);
	mTerrainRenderer->loadPlayerBelowLake(pPlayerBelowLake);
	mTerrainRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);

	
	// Render Terrain
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

// Set FPS Counter
void MainRenderer::setFPS(int pFPS)
{
	mFPS = pFPS;
}

// Render Debug information
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

// Adding things to the render list

// Entity
void MainRenderer::addToList(Entity &pEntity)
{
	mEntities.push_back(pEntity);
}
// Waterdrop
void MainRenderer::addToList(Waterdrop &pWaterDrop)
{
	mWaterDrop.push_back(pWaterDrop);
}
// Objects
void MainRenderer::addToList(Object &pObject)
{
	mObjects.push_back(pObject);
}
// Entity with given Rendermode
void MainRenderer::addToList(Entity &pEntity, RenderMode pMode)
{
	mSpecial.push_back(pEntity);
	mRenderMode.push_back(pMode);
}

// Terrain
void MainRenderer::addToList(Terrain &pTerrain)
{
	mTerrains.push_back(pTerrain);
}

// Setting Draw Mode 
void MainRenderer::setDrawMode(bool pMode)
{
	drawMode = pMode;
}
// Returns the Draw Mode
bool MainRenderer::getDrawMode() const
{
	return drawMode;
}

// Setting the Normal Mode
void MainRenderer::setNormalMode(bool pMode)
{
	normalMode = pMode;
}

// Returns the Normal  Mode
bool MainRenderer::getNormalMode() const
{
	return normalMode;
}

// Setting the Debug Mode
void MainRenderer::setDebugMode(bool pMode)
{
	debugMode = pMode;
}

// Returns the Debug Mode
bool MainRenderer::getDebugMode() const
{
	return debugMode;
}


// Clears the whole list
void MainRenderer::clearLists()
{
	mEntities.clear();
	mTerrains.clear();
	mSpecial.clear();
	mRenderMode.clear();
}
