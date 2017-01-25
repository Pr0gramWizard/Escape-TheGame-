#include "game.hpp"

const GLfloat Game::RED = 0.5;
const GLfloat Game::GREEN = 0.5;
const GLfloat Game::BLUE = 0.5;

Game::Game()
{

}

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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	mPlayer = new Player(glm::vec3(0, 0, 0), 1, "Hans Dieter", this->getHeight(), this->getWidth());

	mSkybox = new Skybox();



	
}


Game::~Game()
{
	delete mPlayer;
}

bool Game::gameLoop()
{
	Loader* loader = new Loader();
	
	Terrain terrain(0, 0, 0, 10, "Test", loader, "./terrain/res/ColorBoden3.png");
	Terrain terrain2(0, 0, 5, 10, "Test2", loader, "./terrain/res/Decke.png");
	std::list<Terrain> terrains;
	terrains.push_back(terrain);
	terrains.push_back(terrain2);

	mRenderer = new MainRenderer(mPlayer->getProjectionMatrix(), mPlayer);
	mRenderer->addToList(terrain);
	mRenderer->addToList(terrain2);

	Object* Torch = new Object("object/res/torch/torch.obj", glm::vec3(0,0,0));
	ObjectShader ObjectShader("shaders/object.vert", "shaders/object.frag");
	ObjectRenderer ObjectRenderer(&ObjectShader, mPlayer->getProjectionMatrix());
	//**** LAKE STUFF ****
	LakeFrameBuffers* lfbos = new LakeFrameBuffers(mWidth, mHeight);
	LakeShader* lakeshader = new LakeShader("shaders/lake.vert", "shaders/lake.frag");
	LakeRenderer* lakerenderer = new LakeRenderer(lakeshader, mPlayer->getProjectionMatrix(), lfbos);
	Lake* lake = new Lake(75, -6, 80, 50, 50, "Lake", loader);
	//**** END LAKE STUFF ****

	//**** LIGHT STUFF ****
	//Light* sun = new Light(glm::vec3(250, 1, 250), glm::vec3(1, 1, 0), glm::vec3(1, 0.01, 0.002));
	Light* sun = new Light(glm::vec3(0, 1, 0), glm::vec3(0.4f, 0.4f, 0.4f));
	Light* sun2 = new Light(glm::vec3(500, 20, 0), glm::vec3(1.0f, 1.0f, 0.4f));
	Light* sun3 = new Light(glm::vec3(0, 20, 500), glm::vec3(0.0f, 0.0f, 10.0f));
	Light* sun4 = new Light(glm::vec3(500, 20, 500), glm::vec3(0.0f, 10.0f, 0.0f));
	//Light* lamp = new Light(mPlayer->getCameraPosition(), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1, 0.01, 0.002));
	Light* lamp = new Light(glm::vec3(45.0f, terrain.getHeight(45.0f, 45.0f) + 15, 45.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(1, 0.01, 0.002));
	vector<Light*> lights;
	lights.push_back(sun);
	// lights.push_back(sun2);
	// lights.push_back(sun3);
	// lights.push_back(sun4);
	// lights.push_back(lamp);

	irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();

	SoundEngine->play2D("audio/MainTheme.mp3", GL_TRUE);


	SoundEngine->setSoundVolume(0.1f);

	mSkybox->addTexture("skybox/res/top.jpg");
	mSkybox->addTexture("skybox/res/bottom.jpg");
	mSkybox->addTexture("skybox/res/back.jpg");
	mSkybox->addTexture("skybox/res/front.jpg");
	mSkybox->addTexture("skybox/res/left.jpg");
	mSkybox->addTexture("skybox/res/right.jpg");

	mSkybox->setCubeMapTexture(mSkybox->loadTexture());

	mRenderer->addToList(mSkybox);

	


	// Game loop
	while (!glfwWindowShouldClose(this->getWindow()))
	{
	
		
		// Calculate deltatime of current frame
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		//do_movement();

		if (Keyboard::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			mPlayer->setSprint(true);
		}

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

		mPlayer->move(&terrain, deltaTime);

		glEnable(GL_CLIP_DISTANCE0);
		glEnable(GL_TEXTURE_2D);
		
		// reflection
		lfbos->bindReflectionFrameBuffer();
		float distance = 2 * (mPlayer->getCameraPosition().y - lake->getWorldY());
		mPlayer->getCamera()->incYPosition(-distance);
		mPlayer->getCamera()->invertPitch();
	


		// render to buffer
		mRenderer->render(mPlayer->getViewMatrix(), lights, glm::vec4(0, 1, 0, -lake->getWorldY() + 0.4), Game::RED, Game::GREEN, Game::BLUE);
		// move camera back
		mPlayer->getCamera()->incYPosition(distance);
		mPlayer->getCamera()->invertPitch();

		// refraction
		lfbos->bindRefractionFrameBuffer();
		mRenderer->render(mPlayer->getViewMatrix(), lights, glm::vec4(0, -1, 0, lake->getWorldY() + 0.4), Game::RED, Game::GREEN, Game::BLUE);

		// actual rendering
		glDisable(GL_CLIP_DISTANCE0);
		lfbos->unbindCurrentFrameBuffer();
		mRenderer->render(mPlayer->getViewMatrix(), lights, glm::vec4(0, -1, 0, 10000), Game::RED, Game::GREEN, Game::BLUE);

		// render water
		lake->updateHeights(deltaTime);
		lakerenderer->render(deltaTime, mPlayer->getViewMatrix(), *lake, lights, Game::RED, Game::GREEN, Game::BLUE);

		// Render Debug Information
		mRenderer->renderDebugInformation();

		/*
		ObjectRenderer.startShader();
		ObjectRenderer.loadModelMatrix(Torch);
		ObjectRenderer.loadViewMatrix(mPlayer->getViewMatrix());
		ObjectRenderer.addToList(Torch);
		Torch->setPosition(mPlayer->getPosition() + glm::vec3(0.0f, 1.0f, -1.0f));
		ObjectRenderer.render();
		ObjectRenderer.stopShader();
		*/
		

		
		// Swap the buffers
		glfwSwapBuffers(this->getWindow());
		

	}
	loader->cleanUp();
	delete loader;
	glfwTerminate();
	return 0;
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
		game->mRenderer->setDrawMode((bool)abs(game->mRenderer->getDrawMode() - 1));

	}

	if (Keyboard::isKeyPressed(GLFW_KEY_F1))
	{
		game->mRenderer->setDebugMode((bool)abs(game->mRenderer->getDrawMode() - 1));

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
