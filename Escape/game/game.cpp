// Inclusion of game declaration
#include "game.hpp"

// Setting up background color of the scene
const GLfloat Game::RED = 0.2f;
const GLfloat Game::GREEN = 0.3f;
const GLfloat Game::BLUE = 0.3f;

// Used for post-processing effects
void RenderQuad();

// Default Constructor 
// (Window Width, Window Height, Window Title)
Game::Game(GLuint pWidth, GLuint pHeight, const char* pWindowTitle)
{
	// Setting window height
	setHeight(pHeight);
	// Setting window width
	setWidth(pWidth);
	// Setting window title
	setTitle(pWindowTitle);

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object (Fullscreen Mode)
	
	setWindow(glfwCreateWindow(getWidth(), getHeight(), getTitle(),NULL,NULL));


	//	DEBUG MODE
	// setWindow(glfwCreateWindow(getWidth(), getHeight(), getTitle(), NULL, NULL));

	// Mark context
	glfwMakeContextCurrent(this->getWindow());


	// Set the required callback functions
	// Create callback to the game
	glfwSetWindowUserPointer(this->getWindow(), this);
	// Create callback to keyboard
	glfwSetKeyCallback(this->getWindow(), key_callback);
	// Create callback to cursor 
	glfwSetCursorPosCallback(this->getWindow(), mouse_callback);
	// Create callback to scroll
	glfwSetScrollCallback(this->getWindow(), scroll_callback);
	// Remove cursor
	glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	GLFWimage icons[1];
	icons[0].pixels = SOIL_load_image("./resources/icon.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(this->getWindow(), 1, icons);
	SOIL_free_image_data(icons[0].pixels);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	// Retrieving window height/width
	glfwGetFramebufferSize(this->getWindow(), &width, &height);
	glViewport(0, 0, width, height);

	glfwSetWindowCenter(this->getWindow());

	// Enable 3D
	glEnable(GL_DEPTH_TEST);

	// Cull back faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/*
		Several predefined spawn locations
		Mainly used for Debugging purpose
	*/

	// Spawn Location
	SpawnLocation.x = 61;
	SpawnLocation.y = 4;
	SpawnLocation.z = 70;

	// Create player and set his position
	mPlayer = new Player(SpawnLocation, 0.5f, "Player", this->getHeight(), this->getWidth());
}


// Main Game Loop
bool Game::gameLoop()
{
	// Create an instance of a new loader
	Loader* loader = new Loader();

	// Create texturepacks:

	// Floor texturepack
	std::vector<std::string> BodenTexturePack;
	BodenTexturePack.push_back("./terrain/res/texture/normal/stone.jpg");
	BodenTexturePack.push_back("./terrain/res/texture/normal/gravel.jpg");
	BodenTexturePack.push_back("./terrain/res/texture/normal/dirt.jpg");
	BodenTexturePack.push_back("./terrain/res/texture/normal/mossystone.jpg");
	BodenTexturePack.push_back("./terrain/res/texture/poly/blendBoden.png");

	// Ceiling texturepack
	std::vector<std::string> DeckenTexturePack;
	DeckenTexturePack.push_back("./terrain/res/texture/normal/stone.jpg");
	DeckenTexturePack.push_back("./terrain/res/texture/poly/red.jpg");
	DeckenTexturePack.push_back("./terrain/res/texture/poly/cyan.jpg");
	DeckenTexturePack.push_back("./terrain/res/texture/poly/purple.jpg");
	DeckenTexturePack.push_back("./terrain/res/texture/poly/blendMapDecke.png");

	// Create Floor terrain
	Terrain Boden(0, 0, 0, 5, "Boden", loader, "./terrain/res/03.png",false, BodenTexturePack);
	// Create Ceiling terrain
	Terrain Decke(0, 0, -2.7f, 15, "Decke", loader, "./terrain/res/Decke.png",true, DeckenTexturePack);

	// List of all terrains
	std::list<Terrain> allTerrain;
	// Insert all current terrains
	allTerrain.push_back(Boden);

	// Create new instance of renderer
	mRenderer = new MainRenderer(mPlayer->getProjectionMatrix(), mPlayer);
	// Add terrain to render list
	mRenderer->addToList(Boden);
		
	//**** LIGHT STUFF ****

	// Global Sun Light
	Light* sun = new Light(glm::vec3(0,100,0), glm::vec3(1.0f, 1.0f, 0.7f));

	// Vector of all lights
	vector<Light*> allLights;
	// Add lights to the list of lights
	allLights.push_back(sun);

	//**** END LIGHT STUFF ****

	GLfloat lastTime = (GLfloat) glfwGetTime();

	int frames = 0;

	float timeElapsed = 0.0f;

	// Game loop
	while (!glfwWindowShouldClose(this->getWindow()))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		frames++;

		// FPS Counter
		if (currentFrame - lastTime >= 1.0)
		{
			mRenderer->setFPS(frames);
			frames = 0;
			lastTime += 1.0f;
		}

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Controlling the sound
		this->controlSound();

		// Calculating the player movement
		mPlayer->move(&Boden,&Decke, deltaTime, false);
		mRenderer->render(mPlayer->getViewMatrix(), allLights, Game::RED, Game::GREEN, Game::BLUE, deltaTime);
	
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

void Game::glfwSetWindowCenter(GLFWwindow* window) {
	// Get window position and size
	int window_x, window_y;
	glfwGetWindowPos(window, &window_x, &window_y);

	int window_width, window_height;
	glfwGetWindowSize(window, &window_width, &window_height);

	// Halve the window size and use it to adjust the window position to the center of the window
	window_width = (int)(window_width * 0.5);
	window_height = (int)(window_height * 0.5);

	window_x += window_width;
	window_y += window_height;

	// Get the list of monitors
	int monitors_length;
	GLFWmonitor **monitors = glfwGetMonitors(&monitors_length);

	if (monitors == NULL) {
		// Got no monitors back
		return;
	}

	// Figure out which monitor the window is in
	GLFWmonitor *owner = NULL;
	int owner_x, owner_y, owner_width, owner_height;

	for (int i = 0; i < monitors_length; i++) {
		// Get the monitor position
		int monitor_x, monitor_y;
		glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

		// Get the monitor size from its video mode
		int monitor_width, monitor_height;
		GLFWvidmode *monitor_vidmode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);

		if (monitor_vidmode == NULL) {
			// Video mode is required for width and height, so skip this monitor
			continue;

		}
		else {
			monitor_width = monitor_vidmode->width;
			monitor_height = monitor_vidmode->height;
		}

		// Set the owner to this monitor if the center of the window is within its bounding box
		if ((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
			owner = monitors[i];

			owner_x = monitor_x;
			owner_y = monitor_y;

			owner_width = monitor_width;
			owner_height = monitor_height;
		}
	}

	if (owner != NULL) {
		// Set the window position to the center of the owner monitor
		int scaledOwnerWidth = (int)(owner_width * 0.5);
		int scaledOwnerHeight = (int)(owner_height * 0.5);
		glfwSetWindowPos(window, owner_x + scaledOwnerWidth - window_width, owner_y + scaledOwnerHeight - window_height);
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

	if (Keyboard::isKeyPressed(GLFW_KEY_F)) {
		game->mPlayer->setIsFlying(!game->mPlayer->isFlying());
		std::clog << game->mPlayer->isFlying() << std::endl;
		if (game->mPlayer->isFlying()) {
			game->mPlayer->setUpSpeed(10.0f);
			game->mPlayer->setMovementSpeed(30.0f);
			game->mPlayer->setGravity(0.0f);
		}
		else {
			game->mPlayer->setGravity(-30.0f);
		}
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

	if (Keyboard::isKeyPressed(GLFW_KEY_F1)) {
		game->mPlayer->setPosition(game->SpawnLocation);
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
