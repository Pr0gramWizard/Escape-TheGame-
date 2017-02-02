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
	setWindow(glfwCreateWindow(getWidth(), getHeight(), getTitle(), glfwGetPrimaryMonitor(),NULL));
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

	glm::vec3 Origin(0);
	glm::vec3 Sea(78, 0, 61);
	glm::vec3 WayToLookOut(63, 0, 23);

	mPlayer = new Player(Sea, 1, "Hans Dieter", this->getHeight(), this->getWidth());	
}



bool Game::gameLoop()
{
	Loader* loader = new Loader();
	
	Terrain floor(0, 0, 0, 10, "Test", loader, "./terrain/res/BodenSee.png");
	Terrain ceiling(0, 0, 5, 10, "Test2", loader, "./terrain/res/Decke.png");

	std::list<Terrain> terrains;
	terrains.push_back(floor);
	terrains.push_back(ceiling);

	mRenderer = new MainRenderer(mPlayer->getProjectionMatrix(), mPlayer);
	mRenderer->addToList(floor);
	mRenderer->addToList(ceiling);


	

	
	//**** LAKE STUFF ****
	LakeFrameBuffers* lfbos = new LakeFrameBuffers(mWidth, mHeight);
	LakeShader* lakeshader = new LakeShader("shaders/lake.vert", "shaders/lake.frag");
	LakeRenderer* lakerenderer = new LakeRenderer(lakeshader, mPlayer->getProjectionMatrix(), lfbos);
	Lake* lake = new Lake(84, -2, 28, 50, 50, "Lake", loader);
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
	Light* sun = new Light(glm::vec3(0, 100000, 0), glm::vec3(0.1f, 0.1f, 0.1f));
	Light* sun2 = new Light(glm::vec3(112, 6, 10), glm::vec3(1.0f, 0.6f, 0.0f));
	Light* sun3 = new Light(glm::vec3(0, 20, 500), glm::vec3(0.0f, 0.0f, 10.0f));
	Light* sun4 = new Light(glm::vec3(500, 20, 500), glm::vec3(0.0f, 10.0f, 0.0f));
	//Light* lamp = new Light(mPlayer->getCameraPosition(), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1, 0.01, 0.002));
	Light* lamp = new Light(glm::vec3(45.0f, floor.getHeight(45.0f, 45.0f) + 15, 45.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(1, 0.01, 0.002));
	vector<Light*> lights;

	lights.push_back(sun);
	// lights.push_back(sun2);

	// lights.push_back(sun3);
	// lights.push_back(sun4);
	// lights.push_back(lamp);

	SoundEngine = irrklang::createIrrKlangDevice();

	SoundEngine->play2D("audio/MainTheme.mp3", GL_TRUE);


	SoundEngine->setSoundVolume(0.1f);

	GLfloat timeElapsed = 0;

	GLfloat frames = 0;

	// Game loop
	while (!glfwWindowShouldClose(this->getWindow()))
	{
	
		
		// Calculate deltatime of current frame
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		timeElapsed += deltaTime * 10;
		if (timeElapsed > 10.0f)
		{

			std::cout << deltaTime << std::endl;
		}

		

		

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Controlling the sound
		this->controlSound();

		// Calculating the player movement
		mPlayer->move(&floor,&ceiling, deltaTime);	

		glEnable(GL_CLIP_DISTANCE0);
		glEnable(GL_TEXTURE_2D);

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
		mRenderer->render(mPlayer->getViewMatrix(), 0.0f, lights, glm::vec4(0, sign, 0, -sign * lake->getWorldY() + 0.4), Game::RED, Game::GREEN, Game::BLUE);
		// move camera back
		mPlayer->getCamera()->incYPosition(distance);
		mPlayer->getCamera()->invertPitch();

		// refraction
		lfbos->bindRefractionFrameBuffer();
		mRenderer->render(mPlayer->getViewMatrix(), 0.0f, lights, glm::vec4(0, -sign, 0, sign * lake->getWorldY() + 0.4), Game::RED, Game::GREEN, Game::BLUE);
		// actual rendering
		glDisable(GL_CLIP_DISTANCE0);
		lfbos->unbindCurrentFrameBuffer();

		//render to prebloomfbo
		prebloomfbo->bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			/*
			* sign is -1 if player is below the lake
			*/
			mRenderer->render(mPlayer->getViewMatrix(), isPlayerBelowLake, lights, glm::vec4(0, -1, 0, 10000), Game::RED, Game::GREEN, Game::BLUE);
			// Render Debug Information
			mRenderer->renderDebugInformation();
			// render water
			lake->updateHeights(deltaTime);
			lakerenderer->render(deltaTime, mPlayer->getViewMatrix(), *lake, lights, Game::RED, Game::GREEN, Game::BLUE);
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
