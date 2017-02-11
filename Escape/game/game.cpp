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
	
	setWindow(glfwCreateWindow(getWidth(), getHeight(), getTitle(),glfwGetPrimaryMonitor(),NULL));


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

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	// Retrieving window height/width
	glfwGetFramebufferSize(this->getWindow(), &width, &height);
	glViewport(0, 0, width, height);

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
	glm::vec3 Spawn(61,4,70);
	// Lava Room
	glm::vec3 Lava(103,4,85);

	// Create player and set his position
	mPlayer = new Player(Spawn, 0.5f, "Player", this->getHeight(), this->getWidth());
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
	Terrain Boden(0, 0, 0, 5, "Boden", loader, "./terrain/res/Boden.png",false, BodenTexturePack);
	// Create Ceiling terrain
	Terrain Decke(0, 0, -2.7f, 15, "Decke", loader, "./terrain/res/Decke.png",true, DeckenTexturePack);

	// List of all terrains
	std::list<Terrain> allTerrain;
	// Insert all current terrains
	allTerrain.push_back(Decke);
	allTerrain.push_back(Boden);

	// Create new instance of renderer
	mRenderer = new MainRenderer(mPlayer->getProjectionMatrix(), mPlayer);
	// Add terrain to render list
	mRenderer->addToList(Boden);
	mRenderer->addToList(Decke);
	
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
	// Create new light sources

	// Global Sun Light
	Light* sun = new Light(glm::vec3(0, 5, 0), glm::vec3(0.2f, 0.2f, 0.2f));
	// Torch light
	Light* torch = new Light(mPlayer->getPosition(), glm::vec3(0.1f, 0.1f, 0.04f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.1f, 0.4f, 0.0f), 0.1f, 0.5f);
	// Light inside lava room
	Light* LavaLight = new Light(glm::vec3(97.0f, 3.0f, 77.0f), glm::vec3(0.9f, 0.3f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.1f, 0.4f, 0.0f), 0.1f, 0.5f);
	// Another light inside the lava room
	Light* LavaLight2 = new Light(glm::vec3(101.0f, 3.0f, 70.0f), glm::vec3(0.6f, 0.3f, 0.0f), glm::vec3(0.005f, 0.005f, 0.005f), glm::vec3(0.0f, 0.0f, 0.5f), 0.5f, 0.3f);
	// Light inside water room
	Light* WaterLight = new Light(glm::vec3(52.0f, 10.0f, 33.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.1f, 0.4f), 1.0f, 1.0f);

	// Vector of all lights
	vector<Light*> allLights;
	// Add lights to the list of lights
	allLights.push_back(LavaLight);
	allLights.push_back(LavaLight2);
	allLights.push_back(WaterLight);
	allLights.push_back(torch);

	//**** GLOWSTOWNES ****

	// All different glow stone models
	std::vector<GLchar*> GlowStoneModels;
	GlowStoneModels.push_back("./object/res/rocks/rockModelA.obj");
	GlowStoneModels.push_back("./object/res/rocks/rockModelB.obj");
	GlowStoneModels.push_back("./object/res/rocks/rockModelC.obj");
	GlowStoneModels.push_back("./object/res/rocks/rockModelD.obj");
	GlowStoneModels.push_back("./object/res/rocks/rockModelE.obj");

	const char* textureRock = "./object/res/stone/texture.png";


	// Saving all Glowstone Positions
	std::vector<glm::vec3> GlowStonePosition;
	GlowStonePosition.push_back(glm::vec3(52.0f, Boden.getHeight(52.0f, 66.0f) + 0.1f ,66.0f));
	GlowStonePosition.push_back(glm::vec3(75.0f, Boden.getHeight(75.0f, 93.0f) + 0.1f, 93.0f));
	GlowStonePosition.push_back(glm::vec3(58.0f, Boden.getHeight(58.0f, 88.0f) + 0.1f, 88.0f));
	GlowStonePosition.push_back(glm::vec3(54.0f, Decke.getHeight(54.0f, 102.0f) - 0.1f, 102.0f));
	GlowStonePosition.push_back(glm::vec3(61.0f, Boden.getHeight(61.0f, 120.0f) + 0.1f, 120.0f));
	GlowStonePosition.push_back(glm::vec3(70.0f, Boden.getHeight(70.0f, 100.0f) + 0.1f, 100.0f));
	GlowStonePosition.push_back(glm::vec3(85.0f, Decke.getHeight(85.0f, 111.0f) - 0.1f, 111.0f));
	GlowStonePosition.push_back(glm::vec3(87.0f, Boden.getHeight(87.0f, 124.0f) + 0.1f, 124.0f));
	GlowStonePosition.push_back(glm::vec3(106.0f, Boden.getHeight(106.0f, 91.0f) + 0.1f, 91.0f));
	GlowStonePosition.push_back(glm::vec3(82.0f, Boden.getHeight(82.0f, 75.0f) + 0.1f, 75.0f));
	GlowStonePosition.push_back(glm::vec3(91.0f, Boden.getHeight(91.0f, 59.0f) + 0.1f, 59.0f));
	GlowStonePosition.push_back(glm::vec3(103.0f, Boden.getHeight(103.0f, 64.0f) + 0.1f, 64.0f));
	GlowStonePosition.push_back(glm::vec3(86.0f, Decke.getHeight(86.0f, 39.0f) - 0.1f, 39.0f));
	GlowStonePosition.push_back(glm::vec3(51.0f, Boden.getHeight(51.0f, 17.0f) + 0.1f, 17.0f));
	GlowStonePosition.push_back(glm::vec3(44.0f, Boden.getHeight(44.0f, 49.0f) + 0.1f, 49.0f));
	GlowStonePosition.push_back(glm::vec3(46.0f, Boden.getHeight(46.0f, 27.0f) + 0.1f, 27.0f));

	// Random generating Glowstone Sizes
	std::vector<GLfloat> GlowStoneSize;

	// Allocate the memory in the vector
	GlowStoneSize.reserve(13);

	// Minimum size
	GLfloat minStoneSize = 0.5f;
	// Maximum size
	GLfloat maxStoneSize = 1.0f;

	for (unsigned int i = 0; i < GlowStonePosition.size(); ++i)
	{
		GlowStoneSize.push_back(minStoneSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxStoneSize - minStoneSize))));
	}

	// Generating all glowstones
	std::vector<Object> GlowStones;

	// Creating the glowstones
	for (unsigned int i = 0; i < GlowStonePosition.size(); ++i)
	{
		int randomNumber = 0 + (rand() % (int)(4));
		GlowStones.push_back(Object(GlowStoneModels.at(randomNumber), GlowStonePosition.at(i), glm::vec3(0.0f, 0.0f, 0.0f),GlowStoneSize.at(i)));
	}

	// Loading the textures
	for (unsigned int j = 0; j < GlowStones.size(); ++j)
	{
		GlowStones.at(j).loadTexture(textureRock);
	}

	// Create lights inside the cube
	Light* stone1L = new Light(glm::vec3(52, Boden.getHeight(52, 66) + 0.1f, 66), glm::vec3(0.4f, 0.4f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.5f, 0.2f, 0.0f), 0.3f, 0.5f);
	Light* stone2L = new Light(glm::vec3(75, Boden.getHeight(75, 93) + 0.1f, 93), glm::vec3(0.5f, 0.1f, 0.4f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.2f, 0.5f, 0.0f), 0.15f, 0.4f);
	Light* stone3L = new Light(glm::vec3(58, Boden.getHeight(58, 88) + 0.1f, 88), glm::vec3(0.0f, 0.0f, 0.6f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.0f, 0.2f, 0.5f), 0.31f, 0.5f);
	Light* stone4L = new Light(glm::vec3(54, Decke.getHeight(54, 102) - 0.1f, 102), glm::vec3(0.5f, 0.25f, 0.3f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.0f, 0.4f, 0.2f), 0.2f, 0.6f);
	Light* stone5L = new Light(glm::vec3(61, Boden.getHeight(61, 120) + 0.1f, 120), glm::vec3(0.6f, 0.0f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.6f, 0.4f, 0.1f), 0.5f, 0.6f);
	Light* stone6L = new Light(glm::vec3(70, Boden.getHeight(70, 100) + 0.1f, 100), glm::vec3(0.3f, 0.5f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.3f, 0.0f, 0.5f), 0.4f, 0.6f);
	Light* stone7L = new Light(glm::vec3(85, Decke.getHeight(85, 111) - 0.1f, 111), glm::vec3(0.5f, 0.25f, 0.1f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.0f, 0.4f, 0.4f), 0.1f, 0.55f);
	Light* stone9L = new Light(glm::vec3(87, Boden.getHeight(87, 124) + 0.1f, 124), glm::vec3(0.5f, 0.25f, 0.3f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.5f, 0.0f, 0.4f), 0.52f, 0.5f);
	Light* stone10L = new Light(glm::vec3(106, Boden.getHeight(106, 91) + 0.1f, 91), glm::vec3(0.6f, 0.0f, 0.1f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.5f, 0.2f, 0.0f), 0.13f, 0.4f);
	Light* stone11L = new Light(glm::vec3(82, Boden.getHeight(82, 75) + 0.1f, 75), glm::vec3(0.7f, 0.3f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.0f, 0.2f, 0.5f), 0.41f, 0.2f);
	Light* stone12L = new Light(glm::vec3(91, Boden.getHeight(91, 59) + 0.1f, 59), glm::vec3(0.0f, 0.3f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.2f, 0.5f, 0.0f), 0.2f, 0.8f);
	Light* stone13L = new Light(glm::vec3(103, Boden.getHeight(103, 64) + 0.1f, 64), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.5f, 0.1f, 0.4f), 0.4f, 0.5f);
	Light* stone14L = new Light(glm::vec3(86, Decke.getHeight(86, 39) - 0.1f, 39), glm::vec3(0.5f, 0.1f, 0.4f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.1f, 0.5f, 0.1f), 0.15f, 0.65f);
	Light* stone16L = new Light(glm::vec3(51, Boden.getHeight(51, 17) + 0.1f, 17), glm::vec3(0.3f, 0.3f, 0.1f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.1f, 0.5f, 0.0f), 0.56f, 0.6f);
	Light* stone18L = new Light(glm::vec3(44, Boden.getHeight(44, 49) + 0.1f, 49), glm::vec3(2.0, 0.0f, 0.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(0.0f, 3.0f, 0.0f), 0.6f, 0.4f);
	Light* stone19L = new Light(glm::vec3(46, Boden.getHeight(46, 27) + 0.1f, 27), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.001f, 0.001f, 0.01f), glm::vec3(2.5f, 0.0f, 0.0f), 0.3f, 0.5f);

	// Add Stone to render list
	for (unsigned int h = 0; h < GlowStones.size(); ++h)
	{
		mRenderer->addToList(GlowStones.at(h));
	}

	// Add Lights to light list
	allLights.push_back(stone1L);
	allLights.push_back(stone2L);
	allLights.push_back(stone3L);
	allLights.push_back(stone4L);
	allLights.push_back(stone5L);
	allLights.push_back(stone6L);
	allLights.push_back(stone7L);
	allLights.push_back(stone9L);
	allLights.push_back(stone10L);
	allLights.push_back(stone11L);
	allLights.push_back(stone12L);
	allLights.push_back(stone13L);
	allLights.push_back(stone14L);
	allLights.push_back(stone16L);
	allLights.push_back(stone18L);
	allLights.push_back(stone19L);

	//**** END GLOWSTONES ****

	//**** WATER DROPS ****

	// Random generating Waterdrop Size and Speed
	std::vector<GLfloat> WaterDropSize;
	std::vector<GLfloat> WaterDropSpeed;

	// Allocate the memory in the vector
	WaterDropSize.reserve(13);
	WaterDropSpeed.reserve(13);

	// Minimum size
	GLfloat minWaterdropSize = 0.06f;
	// Maximum size
	GLfloat maxWaterdropSize = 0.3f;
	// Minimum speed
	GLfloat minWaterdropSpeed = 0.03f;
	// Maximum speed
	GLfloat maxWaterdropSpeed = 0.06f;

	// Creating the 
	for (unsigned int i = 0; i < 13; ++i)
	{
		WaterDropSize.push_back(minWaterdropSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxWaterdropSize - minWaterdropSize))));
	}

	for (unsigned int i = 0; i < 13; ++i)
	{
		WaterDropSpeed.push_back(minWaterdropSpeed + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxWaterdropSpeed - minWaterdropSpeed))));
	}

	std::vector<Waterdrop> ListOfAllWaterdrops;

	GLchar* filePath = "./waterdrop/res/raindrop.obj";
	const char* texturePath = "./waterdrop/res/water.png";

	std::vector<glm::vec3> ListOfWaterDropPosition;

	ListOfWaterDropPosition.push_back(glm::vec3(54.0f, Decke.getHeight(54.0f, 34.0f) + 0.09f, 34.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(55.0f, Decke.getHeight(55.0f, 33.0f) + 0.09f, 33.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(53.0f, Decke.getHeight(53.0f, 34.0f) + 0.09f, 34.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(56.5f, Decke.getHeight(56.5f, 54.0f), 54.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(47.0f, Decke.getHeight(47.0f, 32.0f), 32.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(56.0f, Decke.getHeight(56.0f, 33.0f), 33.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(55.0f, Decke.getHeight(55.0f, 33.0f), 33.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(54.0f, Decke.getHeight(54.0f, 33.0f), 33.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(53.0f, Decke.getHeight(53.0f, 33.0f), 33.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(40.0f, Decke.getHeight(44.0f, 35.0f), 34.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(41.0f, Decke.getHeight(44.0f, 35.0f), 36.0f));
	ListOfWaterDropPosition.push_back(glm::vec3(44.0f, Decke.getHeight(44.0f, 37.0f), 37.0f));

	// Create Waterdrop objects
	for (unsigned int counter = 0; counter < ListOfWaterDropPosition.size(); ++counter)
	{
		ListOfAllWaterdrops.push_back(Waterdrop(filePath, ListOfWaterDropPosition.at(counter), glm::vec3(0.0f, 0.0f, 0.0f), WaterDropSize.at(counter), WaterDropSpeed.at(counter)));
	}

	// Load textures
	for (unsigned int i = 0; i < ListOfWaterDropPosition.size(); ++i)
	{
		ListOfAllWaterdrops.at(i).loadTexture(texturePath);
	}

	// Add to render list
	for (unsigned int j = 0; j < ListOfWaterDropPosition.size(); ++j)
	{
		mRenderer->addToList(ListOfAllWaterdrops.at(j));
	}
	//**** END WATER DROPS

	//**** TORCH STUFF
	Torch* cTorch = new Torch("./torch/res/torch3.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.3f);
	cTorch->loadTexture("./torch/res/wood.png");
	mRenderer->addToList(cTorch);

	//**** END TORCH STUFF
 
	vector<Light*> lights;

	SpotLight* spotlight = new SpotLight(glm::vec3(46.0f, 24.0f, 15.0f), glm::vec3(1.5f,1.5f,1.5f), glm::vec3(56,3,42), 120.0f);
	lakerenderer->startShader();
	lakerenderer->loadLakeSpotLightPosition(spotlight->getPosition());
	lakerenderer->loadLakeSpotLightColor(spotlight->getColor());
	lakerenderer->loadLakeSpotLightTarget(spotlight->getTarget());
	lakerenderer->loadLakeSpotLightFactor(spotlight->getFactor());
	lakerenderer->stopShader();
	//**** END LIGHT STUFF ****

	//**** GAME MUSIC
	SoundEngine = irrklang::createIrrKlangDevice();
	SoundEngine->play2D("audio/MainTheme.mp3", GL_TRUE);
	SoundEngine->setSoundVolume(0.1f);
	//**** END MUSIC

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
		mPlayer->move(&Boden,&Decke, deltaTime, this->hasWallCollision());
		glm::vec3 playerPos = mPlayer->getCameraPosition();
		torch->setPosition(playerPos - mPlayer->getCamera()->getRight()/2.0f - mPlayer->getViewVector());

		//**** light sorting ****
		float gamma = 0.5f;

		// always use torch
		if (useTorch()) {
			lights.push_back(torch);
		}
		
		float maxDistance = 0.0f;
		unsigned int maxIndex = 5;

		// push first MAX_LIGHTS - 1 lights to lights list and track the one with most distance
		for (unsigned int i = 0; i < MAX_LIGHTS && i < allLights.size(); ++i) {
			float distance = glm::distance(playerPos, allLights[i]->getPosition());
			if (distance > maxDistance) {
				maxDistance = distance;
				maxIndex = i;
			}
			lights.push_back(allLights[i]);
		}

		// check the rest of the lights if one is closer to the player then the furthest already inside lights list
		for (unsigned int j = MAX_LIGHTS - 1; j < allLights.size(); ++j) {
			float distance = glm::distance(playerPos, allLights[j]->getPosition());
			// if found put the light into lights list and search for new max item
			if (distance < maxDistance) {
				lights[maxIndex] = allLights[j];
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

		glm::vec3 lavaPosition = lava->getWorldPos();
		// -0.25f because lava gets pushed down by 0.25 in vertex shader
		bool isPlayerBurning = (playerPosition.y < lava->getWorldY() - 0.25f
			&& playerPosition.x >= lavaPosition.x
			&& playerPosition.x <= lavaPosition.x + lava->LAVA_SIZE
			&& playerPosition.z >= lavaPosition.z
			&& playerPosition.z <= lavaPosition.z + lava->LAVA_SIZE
			);
		mPlayer->setIsBurning(isPlayerBurning);

		float fogDensity = 0.1f;
			//glm::vec4 lakeBounds = glm::vec4(19.0f,6.0f,79.0f,65.0f);
			glm::vec3 lakeMid = glm::vec3(49.0f, 0.0f, 34.5f);
			//glm::vec4 lavaBounds = glm::vec4(82.0f,60.0f,112.0f,95.0f);
			glm::vec3 lavaMid = glm::vec3(97.0f, 0.0f, 77.5f);

			float lavaDist = glm::distance(playerPos, lavaMid);
			float lakeDist = glm::distance(playerPos, lakeMid);

			if (lavaDist < 30.f) {
				if (lavaDist < 20.0f) {
					fogDensity = 0.035f;
					gamma = 0.45f;
						
					lights[0] = stone14L;
					lights[1] = stone10L;
					lights[2] = stone11L;
					lights[3] = stone12L;
					lights[4] = stone13L;
					lights[5] = LavaLight;
				}
				else {
					float alpha = (lavaDist - 20.0f) / 10.0f;
					fogDensity = alpha * fogDensity + (1 - alpha) * 0.035f;
					gamma = alpha * 0.5f + (1 - alpha) * 0.45f;
				}
			} else  if (lakeDist < 38.f) {
				if (lakeDist < 31.0f) {
					fogDensity = 0.01f;
					gamma = 0.7f;
						
					lights[0] = stone13L;
					lights[1] = stone16L;
					lights[2] = stone18L;
					lights[3] = stone19L;
					lights[4] = stone14L;
					lights[5] = WaterLight;
				}
				else {
					float alpha = (lakeDist - 31.0f) / 7.0f;
					fogDensity = alpha * fogDensity + (1 - alpha) * 0.01f;
					gamma = alpha * 0.5f + (1 - alpha) * 0.7f;
				}
			}

			if (!this->hasFog()) {
				fogDensity = 0.0f;
			}

			if (this->useTorch()) {
				lights[0] = torch;
			}
			
		// tell the player if he is under the lake
		mPlayer->setIsBelowLake(isPlayerBelowLake);
		// render to buffer
		mRenderer->render(mPlayer->getViewMatrix(), 0.0f, lights, glm::vec4(0, sign, 0, -sign * lake->getWorldY() + 0.4), Game::RED, Game::GREEN, Game::BLUE, discoTime, fogDensity, 2.0f, deltaTime);
		// move camera back
		mPlayer->getCamera()->incYPosition(distance);
		mPlayer->getCamera()->invertPitch();

		// refraction
		lfbos->bindRefractionFrameBuffer();
		mRenderer->render(mPlayer->getViewMatrix(), 0.0f, lights, glm::vec4(0, -sign, 0, sign * lake->getWorldY() + 0.4), Game::RED, Game::GREEN, Game::BLUE, discoTime, fogDensity, 2.0f,deltaTime);
		// actual rendering
	
		glDisable(GL_CLIP_DISTANCE0);
		lfbos->unbindCurrentFrameBuffer();




		/*
		mRenderer->render(mPlayer->getViewMatrix(), 0.0f, lights, glm::vec4(0, 1, 0, 100000), Game::RED, Game::GREEN, Game::BLUE, discoTime);
		mRenderer->renderDebugInformation();
		// render water
		lake->updateHeights(deltaTime);
		lakerenderer->render(deltaTime, mPlayer->getViewMatrix(), *lake, lights, Game::RED, Game::GREEN, Game::BLUE, discoTime);
		// render lava
		lavarenderer->render(deltaTime, mPlayer->getViewMatrix(), *lava, lights, Game::RED, Game::GREEN, Game::BLUE, discoTime);
		*/

		//render to prebloomfbo
		prebloomfbo->bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			mRenderer->render(mPlayer->getViewMatrix(), isPlayerBelowLake, lights, glm::vec4(0, -1, 0, 10000), Game::RED, Game::GREEN, Game::BLUE, discoTime, fogDensity, 2.0f, deltaTime);
			// Render Debug Information
			mRenderer->renderDebugInformation();
			// render water
			lake->updateHeights(deltaTime);
			lakerenderer->render(deltaTime, mPlayer->getViewMatrix(), *lake, lights, Game::RED, Game::GREEN, Game::BLUE, discoTime);
			// render lava
			lavarenderer->render(deltaTime, mPlayer->getViewMatrix(), *lava, lights, Game::RED, Game::GREEN, Game::BLUE, discoTime);
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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		finalbloomshader->use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, prebloomfbo->getColorBuffer(0));
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, blurfbos->getLastBluredTexture());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, lava->getBurningTexture());
			finalbloomshader->loadGamma(gamma);
			finalbloomshader->loadIsBurning(mPlayer->isBurning());
			finalbloomshader->loadBloom(this->isBlooming());
			finalbloomshader->loadExposure(1.0f);
			RenderQuad();
		finalbloomshader->unuse();
		glDisable(GL_BLEND);

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


void Game::toggleFog()
{
	this->mFog = !!abs(this->mFog - 1);
	std::cout << "Fog toggled to: " << this->mFog << std::endl;
}

bool Game::hasFog()
{
	return this->mFog;
}

void Game::toggleBloomEffect()
{
	this->mBloomEffect = !!abs(this->mBloomEffect - 1);
	std::cout << "Bloom effect toggled to: " << this->mBloomEffect << std::endl;
}

bool Game::isBlooming()
{
	return this->mBloomEffect;
}

void Game::toggleUseTorch()
{
	this->mUseTorch = !!abs(this->mUseTorch - 1);
	std::cout << "Use torch toggled to: " << this->mUseTorch << std::endl;
}

bool Game::useTorch()
{
	return this->mUseTorch;
}

void Game::toggleWallCollision()
{
	this->mWallCollision = !!abs(this->mWallCollision - 1);
	std::cout << "Wall collision toggled to: " << this->mWallCollision << std::endl;
}

bool Game::hasWallCollision()
{
	return this->mWallCollision;
}

void Game::toggleDisco()
{
	this->mDiscoMode = !!abs(this->mDiscoMode - 1);
	std::cout << "Disco mode toggled to: " << this->mDiscoMode << std::endl;
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

	if (Keyboard::isKeyPressed(GLFW_KEY_F4))
	{
		game->toggleFog();
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_F5))
	{
		game->toggleBloomEffect();
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_F6))
	{
		game->toggleUseTorch();
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_F7))
	{
		game->toggleWallCollision();
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
