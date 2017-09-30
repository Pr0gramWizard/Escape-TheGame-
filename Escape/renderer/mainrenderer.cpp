#include "mainrenderer.hpp"

// Shader locations
const char* MainRenderer::TERRAIN_VERTEX = "shaders/terrain.vert";
const char* MainRenderer::TERRAIN_FRAGMENT = "shaders/terrain.frag";
const char* MainRenderer::GUI_VERTEX = "shaders/gui.vert";
const char* MainRenderer::GUI_FRAGMENT = "shaders/gui.frag";


MainRenderer::MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer)
{
	Loader* cLoader = new Loader();
	// Creating terrain Shader
	TerrainShader* terrainshader = new TerrainShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	// Creating terrain renderer
	mTerrainRenderer = new TerrainRenderer(terrainshader, pProjectionMatrix);

	mGuiShader = new GuiShader(GUI_VERTEX, GUI_FRAGMENT);

	mGuiRenderer = new GuiRenderer(cLoader, mGuiShader);

	GuiTexture temp(cLoader->loadTexture("health.png"), glm::vec2(0.25f, 0.25f), glm::vec2(0.1f, 0.1f));

	mGuiRenderer->addGUI(temp);

	mSkybox = new Skybox();

	mSkybox->addTexture("skybox/res/right.jpg");
	mSkybox->addTexture("skybox/res/left.jpg");
	mSkybox->addTexture("skybox/res/top.jpg");
	mSkybox->addTexture("skybox/res/bottom.jpg");
	mSkybox->addTexture("skybox/res/back.jpg");
	mSkybox->addTexture("skybox/res/front.jpg");

	mSkybox->setCubeMapTexture(mSkybox->loadTexture());

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

void MainRenderer::render(glm::mat4 pViewMatrix, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, float pDelta)
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

	// mSkybox->render(pViewMatrix, mPlayer->getProjectionMatrix());


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
		if (this->getNormalMode())
		{
			mNormalRenderer->render(terrain);
		}
	}


	mGuiRenderer->render();
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
	mTerrains.clear();
}
