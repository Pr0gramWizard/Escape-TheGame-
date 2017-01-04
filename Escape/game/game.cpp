#include "game.hpp"

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

	mPlayer = new Player(glm::vec3(0, 0, 0), 5, "Archie der Entdecker", this->getHeight(), this->getWidth());



	
}


Game::~Game()
{
	delete mPlayer;
}

bool Game::gameLoop()
{

	
	Loader* loader = new Loader();
	
	Terrain terrain(0, 0, 15, "Test", loader);
	std::list<Terrain> terrains;
	terrains.push_back(terrain);

	mRenderer = new MainRenderer(mPlayer->getProjectionMatrix(), mPlayer);
	mRenderer->addToList(terrain);

	//**** LAKE STUFF ****
	LakeFrameBuffers* lfbos = new LakeFrameBuffers(mWidth, mHeight);
	LakeShader* lakeshader = new LakeShader("shaders/lake.vert", "shaders/lake.frag");
	LakeRenderer* lakerenderer = new LakeRenderer(lakeshader, mPlayer->getProjectionMatrix(), lfbos);
	Lake* lake = new Lake(0, -3.5, 0, 20, 50, "Lake", loader);
	//**** END LAKE STUFF ****

	// Object* Nano = new Object("object/res/nanosuit/nanosuit.obj");
	Object* Sphere = new Object("object/res/sphere/Alpha.obj",glm::vec3(16 ,terrain.getHeight(16, 78), 77));
	Object* Cube = new Object("object/res/cube/cube.obj", glm::vec3(0, 1, 0));
	ObjectShader* objectshader = new ObjectShader("shaders/object.vert", "shaders/object.frag");
	ObjectRenderer* objectrender = new ObjectRenderer(objectshader, mPlayer->getProjectionMatrix());

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

		if (Keyboard::isKeyPressed(GLFW_KEY_F2))
		{
			std::cout << mPlayer->getPosition().x << "," << mPlayer->getPosition().y << "," << mPlayer->getPosition().z << std::endl;
		}

		mPlayer->move(&terrain, deltaTime);




		glEnable(GL_CLIP_DISTANCE0);
		
		// reflection
		lfbos->bindReflectionFrameBuffer();
		float distance = 2 * (mPlayer->getCameraPosition().y - lake->getWorldY());
		mPlayer->getCamera()->incYPosition(-distance);
		mPlayer->getCamera()->invertPitch();
		// render to buffer
		mRenderer->render(mPlayer->getViewMatrix(), glm::vec4(0, 1, 0, -lake->getWorldY()));
		// move camera back
		mPlayer->getCamera()->incYPosition(distance);
		mPlayer->getCamera()->invertPitch();

		// refraction
		lfbos->bindRefractionFrameBuffer();
		mRenderer->render(mPlayer->getViewMatrix(), glm::vec4(0, -1, 0, lake->getWorldY() + 0.4));

		// actual rendering
		glDisable(GL_CLIP_DISTANCE0);
		lfbos->unbindCurrentFrameBuffer();
		mRenderer->render(mPlayer->getViewMatrix(), glm::vec4(0, -1, 0, 10000));

		// render water
		/*lake->updateHeights();
		lakerenderer->startShader();
		lakerenderer->loadViewMatrix(mPlayer->getViewMatrix());
		lakerenderer->render(*lake);
		lakerenderer->stopShader();*/

		
		/*
		objectrender->startShader();
		// objectrender->loadModelMatrix(Sphere);
		// objectrender->addToList(Sphere);
		objectrender->loadModelMatrix(Cube);
		objectrender->addToList(Cube);
		objectrender->loadViewMatrix(mPlayer->getViewMatrix());
		objectrender->render();
		objectrender->stopShader();
		*/
		// Swap the buffers
		glfwSwapBuffers(this->getWindow());
		

	}
	// delete Nano;
	delete Sphere;
	delete objectshader;
	delete objectrender;
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
