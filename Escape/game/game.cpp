#include "game.hpp"

const GLfloat Game::RED = 0.2f;
const GLfloat Game::GREEN = 0.3f;
const GLfloat Game::BLUE = 0.3f;

// Used for post-processing effects
void RenderQuad();

Game::Game(GLuint pWidth, GLuint pHeight, const char* pWindowTitle)
{
	setHeight(pHeight);
	setWidth(pWidth);
	setTitle(pWindowTitle);
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	

	// Create a GLFWwindow object that we can use for GLFW's functions
	setWindow(glfwCreateWindow(getWidth(), getHeight(), getTitle(),glfwGetPrimaryMonitor(),NULL));
	glfwMakeContextCurrent(this->getWindow());


	// Set the required callback functions
	glfwSetWindowUserPointer(this->getWindow(), this);
	glfwSetKeyCallback(this->getWindow(), key_callback);
	glfwSetCursorPosCallback(this->getWindow(), mouse_callback);
	glfwSetScrollCallback(this->getWindow(), scroll_callback);
	//Remove Null + remove comment to get fullscreen
	glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(this->getWindow(), &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	// Cull back faces
	/*
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	*/

	glm::vec3 Spawn(62,4,64);
	glm::vec3 Lava(103,4,85);

	mPlayer = new Player(Spawn, 0.5f, "Player", this->getHeight(), this->getWidth());
}



bool Game::gameLoop()
{

	Loader* loader = new Loader();

	Terrain Boden(0, 0, 0, 5, "Boden", loader, "./terrain/res/Boden.png");
	Terrain Decke(0, 0, -2.5f, 15, "Decke", loader, "./terrain/res/Decke.png",true);

	std::list<Terrain> allTerrain;

	allTerrain.push_back(Decke);
	allTerrain.push_back(Boden);

	mRenderer = new MainRenderer(mPlayer->getProjectionMatrix(), mPlayer);

	mRenderer->addToList(Boden);
	mRenderer->addToList(Decke);
	
	glDisable(GL_CULL_FACE);

	
	

	//**** LAKE STUFF ****
	LakeFrameBuffers* lfbos = new LakeFrameBuffers(mWidth, mHeight);
	LakeShader* lakeshader = new LakeShader("shaders/lake.vert", "shaders/lake.frag");
	LakeRenderer* lakerenderer = new LakeRenderer(lakeshader, mPlayer->getProjectionMatrix(), lfbos);
	Lake* lake = new Lake(29, 3, 16, 50, 50, "Lake", loader);
	//**** END LAKE STUFF ****

	//**** LAVA STUFF ****
	LavaShader* lavashader = new LavaShader("shaders/lava.vert", "shaders/lava.frag");
	LavaRenderer* lavarenderer = new LavaRenderer(lavashader, mPlayer->getProjectionMatrix());
	Lava* lava = new Lava(80, 4.0f, 60, 50, "Lava", loader);
	//**** END LAKE STUFF ****

	//**** BLUR STUFF ****
	BlurShader *blurshader = new BlurShader("shaders/blur.vert", "shaders/blur.frag");
	BlurFrameBuffers *blurfbos = new BlurFrameBuffers(blurshader, mWidth, mHeight);
	//**** END BLUR STUFF ****

	//**** BLOOM STUFF ****
	PreBloomFBO *prebloomfbo = new PreBloomFBO(mWidth, mHeight);
	FinalBloomShader *finalbloomshader = new FinalBloomShader("shaders/finalbloom.vert", "shaders/finalbloom.frag");
	//**** END BLOOM STUFF ****

	//**** LIGHT STUFF ****
	//Light* sun = new Light(glm::vec3(250, 1, 250), glm::vec3(1, 1, 0), glm::vec3(1, 0.01, 0.002));
	Light* sun = new Light(glm::vec3(0, 5, 0), glm::vec3(0.2f, 0.2f, 0.2f));

	Light* torch = new Light(mPlayer->getPosition(), glm::vec3(0.5f, 0.2f, 0.04f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.1f, 0.4f, 0.0f), 0.1f, 0.5f);

	vector<Light*> allLights;

	// Blue
	Light* LavaLight = new Light(glm::vec3(91.0f,3.0f,77.0f), glm::vec3(0.9f, 0.3f, 0.0f),glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.1f, 0.4f, 0.0f), 0.1f, 0.5f);
	allLights.push_back(LavaLight);
	// Green
	Light* LavaLight2 = new Light(glm::vec3(101.0f,3.0f,70.0f), glm::vec3(0.6f, 0.3f, 0.0f), glm::vec3(0.005f, 0.005f, 0.005f), glm::vec3(0.0f,0.0f,0.5f), 0.5f, 0.3f);
	allLights.push_back(LavaLight2);
	// Red
	Light* WaterLight = new Light(glm::vec3(52.0f,10.0f,33.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.001f, 0.001f, 0.001f), glm::vec3(0.0f,0.2f,0.0f), 1.0f, 1.0f);
	allLights.push_back(WaterLight);
 
	vector<Light*> lights;

	lights.push_back(sun);
	lights.push_back(LavaLight);
	lights.push_back(LavaLight2);
	lights.push_back(WaterLight);

	SpotLight* spotlight = new SpotLight(glm::vec3(-6, 15, -30), glm::vec3(1.5f,1.5f,1.5f), glm::vec3(-7.8f,-1,-21), 120.0f);
	lakerenderer->startShader();
	lakerenderer->loadLakeSpotLightPosition(spotlight->getPosition());
	lakerenderer->loadLakeSpotLightColor(spotlight->getColor());
	lakerenderer->loadLakeSpotLightTarget(spotlight->getTarget());
	lakerenderer->loadLakeSpotLightFactor(spotlight->getFactor());
	lakerenderer->stopShader();
	//**** END LIGHT STUFF ****

	
	/*
	//**** SHADOW STUFF ****
	ShadowShader *shadowshader = new ShadowShader("shaders/shadow.vert", "shaders/shadow.frag", "shaders/shadow.gs");
	ShadowFrameBuffer *shadowFBO = new ShadowFrameBuffer(mWidth, mHeight);

	Light* LavaLight2 = new Light(glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.1f, 0.4f, 0.0f), 0.1f, 0.5f);
	lights.push_back(LavaLight2);

	//test shadow with one light and one terrain
	shadowFBO->bindShadowFrameBuffer();
	// need to clear for every light
	shadowshader->use();
	// maybe change!
	shadowshader->loadFarplane(25.0f);

	// load light source
	shadowshader->loadModelMatrix(Decke.getModelMatrix());
	shadowshader->loadShadowMatrices(shadowFBO->getShadowTransforms(LavaLight2->getPosition()));

	// render scene to shadow map
	mRenderer->renderSceneForDepthCubeMap(shadowshader);

	// save depth cubemap in light
	LavaLight2->setDepthCubemap(shadowFBO->getDepthCubemap());
	cout << LavaLight2->getDepthCubemap() << " is the id of the DepthCubeMap" << endl;
	

	shadowshader->unuse();
	shadowFBO->unbindShadowFrameBuffer();

	//**** END SHADOW STUFF ****
	*/
	SoundEngine = irrklang::createIrrKlangDevice();

	SoundEngine->play2D("audio/MainTheme.mp3", GL_TRUE);


	SoundEngine->setSoundVolume(0.1f);


	/*TEST*/
	GLfloat lastTime = (GLfloat) glfwGetTime();

	int frames = 0;

	// Game loop
	while (!glfwWindowShouldClose(this->getWindow()))
	{
	
		
		// Calculate deltatime of current frame
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		frames++;

		if (currentFrame - lastTime >= 1.0)
		{
			// float fps = 1000.0f / (float)frames;
			mRenderer->setFPS(frames);
			frames = 0;
			lastTime += 1.0f;

		}
		
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Controlling the sound
		this->controlSound();

		// Calculating the player movement
		mPlayer->move(&Boden,&Decke, deltaTime);
		glm::vec3 playerPos = mPlayer->getCameraPosition();
		torch->setPosition(playerPos - mPlayer->getCamera()->getRight() - mPlayer->getViewVector());

		//**** light sorting ****

		// always use torch
		lights.push_back(torch);
		
		float maxDistance = 0.0f;
		unsigned int maxIndex = 1;

		// push first MAX_LIGHTS - 1 lights to lights list and track the one with most distance
		for (unsigned int i = 1; i < MAX_LIGHTS && i < allLights.size(); ++i) {
			float distance = glm::distance(playerPos, allLights[i]->getPosition());
			if (distance > maxDistance) {
				maxDistance = distance;
				maxIndex = i;
			}
			lights.push_back(allLights[i]);
		}

		// check the rest of the lights if one is closer to the player then the furthest already inside lights list
		for (unsigned int j = MAX_LIGHTS; j < allLights.size(); ++j) {
			float distance = glm::distance(playerPos, allLights[j]->getPosition());
			// if found put the light into lights list and search for new max item
			if (distance < maxDistance) {
				lights[maxDistance] = allLights[j];
				maxDistance = 0.0f;
				maxIndex = 1;
				// find new max
				for (unsigned int k = 1; k < lights.size(); ++k) {
					float distance = glm::distance(playerPos, lights[k]->getPosition());
					if (distance > maxDistance) {
						maxDistance = distance;
						maxIndex = k;
					}
				}
			}
		}

		// always use this light
		//lights.push_back(sun);

		// put needed lights in the list
		//lights.push_back(LavaLight);
		// lights.push_back(LavaLight2);
		
		//lights.push_back(stoneB);
		//lights.push_back(stoneC);

		//**** End light sorting ****

		glEnable(GL_CLIP_DISTANCE0);
		// glEnable(GL_TEXTURE_2D);

		// check for disco
		bool discoTime = this->discoDiscoBoomBoom();
		if (discoTime) {
			for (Light *light : lights)
			{
				light->incDiscoTime(deltaTime);
			}
		}
		//Particles->render(mPlayer->getViewMatrix());
		
		// reflection
		lfbos->bindReflectionFrameBuffer();
		float distance = 2 * (mPlayer->getCameraPosition().y - lake->getWorldY());
		mPlayer->getCamera()->incYPosition(-distance);
		mPlayer->getCamera()->invertPitch();
		
		//calculate sign and if the player is below the lake plane
		glm::vec3 playerPosition = mPlayer->getPosition();
		glm::vec3 lakePosition = lake->getWorldPos();
		float sign = (playerPosition.y + mPlayer->getHeight() < lake->getWorldY()) ? -1.0f : 1.0f;
		bool isPlayerBelowLake = (sign == -1 
			&& playerPosition.x >= lakePosition.x 
			&& playerPosition.x <= lakePosition.x + lake->LAKE_SIZE
			&& playerPosition.z >= lakePosition.z
			&& playerPosition.z <= lakePosition.z + lake->LAKE_SIZE
		);
		// tell the player if he is under the lake
		mPlayer->setIsBelowLake(isPlayerBelowLake);
		// render to buffer
		mRenderer->render(mPlayer->getViewMatrix(), 0.0f, lights, glm::vec4(0, sign, 0, -sign * lake->getWorldY() - 0.4), Game::RED, Game::GREEN, Game::BLUE, discoTime);
		// move camera back
		mPlayer->getCamera()->incYPosition(distance);
		mPlayer->getCamera()->invertPitch();

		// refraction
		lfbos->bindRefractionFrameBuffer();
		mRenderer->render(mPlayer->getViewMatrix(), 0.0f, lights, glm::vec4(0, -sign, 0, sign * lake->getWorldY() + 0.4), Game::RED, Game::GREEN, Game::BLUE, discoTime);
		// actual rendering
	
		glDisable(GL_CLIP_DISTANCE0);
		lfbos->unbindCurrentFrameBuffer();
		
		mRenderer->render(mPlayer->getViewMatrix(), 0.0f, lights, glm::vec4(0, 1, 0, 100000), Game::RED, Game::GREEN, Game::BLUE, discoTime);
		mRenderer->renderDebugInformation();
		// render water
		lake->updateHeights(deltaTime);
		lakerenderer->render(deltaTime, mPlayer->getViewMatrix(), *lake, lights, Game::RED, Game::GREEN, Game::BLUE, discoTime);
		// render lava
		lavarenderer->render(deltaTime, mPlayer->getViewMatrix(), *lava, lights, Game::RED, Game::GREEN, Game::BLUE, discoTime);

		/*
		//render to prebloomfbo
		prebloomfbo->bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// sign is -1 if player is below the lake
			
			mRenderer->render(mPlayer->getViewMatrix(), isPlayerBelowLake, lights, glm::vec4(0, -1, 0, 10000), Game::RED, Game::GREEN, Game::BLUE, discoTime);
			// Render Debug Information
			mRenderer->renderDebugInformation();
			// render water
			lake->updateHeights(deltaTime);
			lakerenderer->render(deltaTime, mPlayer->getViewMatrix(), *lake, lights, Game::RED, Game::GREEN, Game::BLUE, discoTime);
		prebloomfbo->unbind();

		// Blur bright fragments w/ two-pass Gaussian Blur
		GLboolean first_iteration = true;
		GLuint amount = 10;
		blurfbos->setHorizontal(true);
		blurfbos->startShader();
		glActiveTexture(GL_TEXTURE0);
			for (GLuint i = 0; i < amount; i++)
			{
				blurfbos->prepare();
				glBindTexture(GL_TEXTURE_2D, first_iteration ? prebloomfbo->getColorBuffer(1) : blurfbos->getLastBluredTexture());  // bind texture of other framebuffer (or scene if first iteration)
				RenderQuad();
				blurfbos->invertHorizontal();
				if (first_iteration)
				{
					first_iteration = false;
				}	
			}
		blurfbos->stopShader();
		blurfbos->unbind();

		// Now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		finalbloomshader->use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, prebloomfbo->getColorBuffer(0));
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, blurfbos->getLastBluredTexture());
			finalbloomshader->loadBloom(true);
			finalbloomshader->loadExposure(1.0f);
			RenderQuad();
		finalbloomshader->unuse();

		
		*/

		// Clear lists
		lights.clear();

		// Swap the buffers
		glfwSwapBuffers(this->getWindow());
		

	}
	loader->cleanUp();
	delete loader;
	glfwTerminate();
	return 0;
}

void Game::controlSound()
{
	if (Keyboard::isKeyPressed(GLFW_KEY_KP_SUBTRACT))
	{
		if (SoundEngine->getSoundVolume() <= 0.0f)
		{
			SoundEngine->setSoundVolume(0.0f);
		}
		else
		{
			SoundEngine->setSoundVolume(SoundEngine->getSoundVolume() - (0.5f * deltaTime));
		}
		std::cout << SoundEngine->getSoundVolume() << std::endl;
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_KP_ADD))
	{
		if (SoundEngine->getSoundVolume() >= 1.0f)
		{
			SoundEngine->setSoundVolume(1.0f);
		}
		else
		{
			SoundEngine->setSoundVolume(SoundEngine->getSoundVolume() + (0.5f * deltaTime));
		}
		std::cout << SoundEngine->getSoundVolume() << std::endl;
	}
}

// RenderQuad() Renders a 1x1 quad in NDC, best used for framebuffer color targets
// and post-processing effects.
GLuint quadVAO = 0;
GLuint quadVBO;
void RenderQuad()
{
	if (quadVAO == 0)
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}



Game::~Game()
{
	delete mPlayer;
}

// Moves/alters the camera positions based on user input
void Game::do_movement()
{

	// Camera controls
	if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
		mPlayer->ProcessKeyboard(FORWARD, deltaTime);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
		mPlayer->ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
		mPlayer->ProcessKeyboard(LEFT, deltaTime);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
		mPlayer->ProcessKeyboard(RIGHT, deltaTime);
	}



}


void Game::toggleDisco()
{
	this->mDiscoMode = !!abs(this->mDiscoMode - 1);
	std::cout << "Disco Mode toggled to: " << this->mDiscoMode << std::endl;
}

bool Game::discoDiscoBoomBoom()
{
	return this->mDiscoMode;
}

// Is called whenever a key is pressed/released via GLFW
void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	Game* game = reinterpret_cast<Game *>(glfwGetWindowUserPointer(window));
	
	// std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Keyboard::setKeyPressed(key, true);
		else if (action == GLFW_RELEASE)
			Keyboard::setKeyPressed(key, false);

	}


	if (Keyboard::isKeyPressed(GLFW_KEY_Q))
	{
		bool DrawMode = !!abs(game->mRenderer->getDrawMode() - 1);
		game->mRenderer->setDrawMode(DrawMode);

	}

	if (Keyboard::isKeyPressed(GLFW_KEY_F1))
	{
		bool DebugMode = !!abs(game->mRenderer->getDrawMode() - 1);
		game->mRenderer->setDebugMode(DebugMode);
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_F2))
	{
		bool NormalMode = !!abs(game->mRenderer->getNormalMode() - 1);
		game->mRenderer->setNormalMode(NormalMode);
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_F8))
	{
		game->toggleDisco();
	}

}

void Game::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Game* game = reinterpret_cast<Game *>(glfwGetWindowUserPointer(window));
	if (game->firstMouse)
	{
		game->lastX = (GLfloat)xpos;
		game->lastY = (GLfloat)ypos;
		game->firstMouse = false;
	}

	GLfloat xoffset = (GLfloat)xpos - game->lastX;
	GLfloat yoffset = game->lastY - (GLfloat)ypos;  // Reversed since y-coordinates go from bottom to left

	game->lastX = (GLfloat)xpos;
	game->lastY = (GLfloat)ypos;

	game->mPlayer->ProcessMouseMovement(xoffset, yoffset,game->deltaTime);

	int wHeight, wWidth;
	glfwGetWindowSize(game->getWindow(), &wWidth, &wHeight);

	GLint halfWidth = (GLint) (wWidth / 2.0f);
	GLint halfHeight = (GLint)(wHeight / 2.0f);
	//add this to lock the mouse centered in the screen
	glfwSetCursorPos(game->getWindow(), halfWidth, halfHeight);
	game->lastX = (GLfloat)halfWidth;
	game->lastY = (GLfloat)halfHeight;
}


void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game* game = reinterpret_cast<Game *>(glfwGetWindowUserPointer(window));

	game->mPlayer->ProcessMouseScroll((GLfloat)yoffset);
}

GLFWwindow * Game::getWindow() const
{
	return mWindow;
}

GLuint Game::getWidth() const
{
	return mWidth;
}

GLuint Game::getHeight() const
{
	return mHeight;
}

const char * Game::getTitle() const
{
	return mTitle;
}

void Game::setWindow(GLFWwindow * pWindow)
{
	mWindow = pWindow;
}

void Game::setWidth(GLuint pWidth)
{
	mWidth = pWidth;
}

void Game::setHeight(GLuint pHeight)
{
	mHeight = pHeight;
}

void Game::setTitle(const char * pTitle)
{
	mTitle = pTitle;
}
