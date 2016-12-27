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
	setWindow(glfwCreateWindow(getWidth(), getHeight(), getTitle(), NULL /*glfwGetPrimaryMonitor()*/, NULL));
	glfwMakeContextCurrent(this->getWindow());


	// Set the required callback functions
	glfwSetWindowUserPointer(this->getWindow(), this);
	glfwSetKeyCallback(this->getWindow(), key_callback);
	glfwSetCursorPosCallback(this->getWindow(), mouse_callback);
	glfwSetScrollCallback(this->getWindow(), scroll_callback);
	//Remove Null + remove comment to get fullscreen
	glfwSetInputMode(this->getWindow(), GLFW_CURSOR, NULL /*GLFW_CURSOR_HIDDEN*/);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(this->getWindow(), &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	mPlayer = new Player(glm::vec3(0, 0, 0), 2, "Archie der Entdecker", this->getHeight(), this->getWidth());

}


Game::~Game()
{
	delete mPlayer;
}

bool Game::gameLoop()
{

	Loader* loader = new Loader();

	EntityRenderer* renderer = new EntityRenderer();

	std::vector<float> vertices = {
		0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, -0.5f,
		0.0f, 0.0f, -0.5f,
		0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, -0.5f,
		0.0f, 0.5f, -0.5f,
	};

	std::vector<float> tex = {
		0,0
	};

	std::vector<float> normal = {
		0,1,0
	};

	std::vector<int> indices = {
		// Button Side
		0,1,3,
		1,2,3,
		// Front Side
		0,1,4,
		1,4,5,
		// Right Side
		1,2,5,
		2,5,6,
		// Left Side
		0,3,4,
		3,4,7,
		// Back Side
		2,3,7,
		2,3,6,
		// Top Side
		4,5,7,
		5,6,7

	};

	std::vector<float> VerticesCoordinateSystem = {
		-10.0f, 0.0f, 0.0f,
		10.0f, 0.0f, 0.0f,
		0.0f, -10.0f, 0.0f,
		0.0f, 10.0f, 0.0f,
		0.0f, 0.0f, -10.0f,
		0.0f, 0.0f, 10.0f
	};

	std::vector<int> IndicesCoordianteSystem = {
		0,1,
		2,3,
		4,5,
	};

	Model CoordianteSystem = loader->loadDataToVao(VerticesCoordinateSystem, tex, normal, IndicesCoordianteSystem);

	Model model = loader->loadDataToVao(vertices, tex, normal, indices);

	Entity* BlockA = new Entity(glm::vec3(0, 0, 0), 0, 0, 0, 1, &model);
	Entity* BlockB = new Entity(glm::vec3(1, 0, 0), 0, 0, 0, 2, &model);
	Entity* CoordinateSystem = new Entity(glm::vec3(0, 0, 0), 0, 0, 0, 1, &CoordianteSystem);

	Testshader* testShader = new Testshader("shaders/b.vert", "shaders/a.frag");
	testShader->bindAttribute(0, "position");

	Terrain terrain(0, 0, 0, 128, "Test", loader);
	Testshader* terrainShader = new Testshader("shaders/terrain.vert", "shaders/terrain.frag");
	TerrainRenderer* terrainRenderer = new TerrainRenderer(terrainShader, mPlayer->getProjectionMatrix());
	std::list<Terrain> terrains;
	terrains.push_back(terrain);

	EntityShader* Test = new EntityShader("shaders/b.vert", "shaders/a.frag");

	MainRenderer* mainRenderer = new MainRenderer(mPlayer->getProjectionMatrix());
	mainRenderer->addToList(terrain);

    // Game loop
	while (!glfwWindowShouldClose(this->getWindow()))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		do_movement();

		
		mainRenderer->prepare();
		/*testShader->use();
		BlockA->increaseRotation(0, 1, 0,deltaTime);
		testShader->loadProjectionMatrix(mPlayer->getProjectionMatrix());
		testShader->loadModelMatrix(BlockA->getModelMatrix());
		testShader->loadViewMatrix(mPlayer->getViewMatrix());
		renderer->render(*BlockA, testShader);
		testShader->unuse();
		testShader->use();
		BlockB->increaseRotation(0, -1, 0,deltaTime);
		testShader->loadProjectionMatrix(mPlayer->getProjectionMatrix(mHeight, mWidth));
		testShader->loadModelMatrix(BlockB->getModelMatrix());
		testShader->loadViewMatrix(mPlayer->getViewMatrix());
		renderer->render(*BlockB, testShader);
		testShader->unuse();*/
		testShader->use();
		testShader->loadProjectionMatrix(mPlayer->getProjectionMatrix());
		testShader->loadModelMatrix(CoordinateSystem->getModelMatrix());
		testShader->loadViewMatrix(mPlayer->getViewMatrix());
		renderer->render(*CoordinateSystem, testShader,LINES);
		testShader->unuse();

		mainRenderer->render(mPlayer->getViewMatrix());
		//terrainShader->use();
		//terrainShader->loadViewMatrix(mPlayer->getViewMatrix());
		//terrainRenderer->render(terrain);
		//terrainShader->unuse();
		
		// Swap the buffers
		glfwSwapBuffers(this->getWindow());

	}
	loader->cleanUp();
	delete loader;
	delete renderer;
	glfwTerminate();
	return 0;
}

// Moves/alters the camera positions based on user input
void Game::do_movement()
{

	// Camera controls
	if (keys[GLFW_KEY_W]) {
		mPlayer->ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S]) {
		mPlayer->ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A]) {
		mPlayer->ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D]) {
		mPlayer->ProcessKeyboard(RIGHT, deltaTime);
	}
	if (keys[GLFW_KEY_K]) {
		std::cout << glm::to_string(mPlayer->getViewVector()) << std::endl;
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
			game->keys[key] = true;
		else if (action == GLFW_RELEASE)
			game->keys[key] = false;

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
