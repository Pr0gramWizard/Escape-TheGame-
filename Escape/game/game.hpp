#pragma once
// Standard Input/Output Stream
#include <iostream>
// SOIL
#include <SOIL.h>
// GLEW
#include <glew.h>
// GLFW
#include <glfw3.h>
// List
#include <list>
// 4x4 matrix
#include <mat4x4.hpp>
// 3x1 vector
#include <vec3.hpp>
// Standard Library
#include <stdlib.h>
// Special glm functions
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
// Text Loader class
#include <ft2build.h>
#include FT_FREETYPE_H
// Audio class
#include <irrKlang.h>
// Keyboard class
#include "../input/keyboard.hpp"
// Camera class
#include "../camera/camera.hpp"
// Terrain class
#include "../terrain/terrain.hpp"
// Player class
#include "../player/player.hpp"
// Loader class
#include "../loader/loader.hpp"
// Renderer classes
#include "../terrain/renderer/terrainRenderer.hpp"
#include "../lake/renderer/lakeRenderer.hpp"
#include "../renderer/mainrenderer.hpp"
// Math class
#include "../math/math.hpp"
// Lake class
#include "../lake/lake.hpp"
// Spotlight
#include "../light/spotlight.hpp"
// Terrain Generator
#include "../terrain/generator/TerrainGenerator.hpp"
// Skybox
#include "../skybox/Skybox.hpp"
// Entity
#include "../entity/entity.hpp"
#include "../entity/shader/entityshader.hpp"
// Object
#include "../object/object.hpp"
#include "../object/shader/objectshader.hpp"
#include "../object/renderer/objectrenderer.hpp"



// Declaration of game class
class Game
{
// All public functions of the class
public:
	// Constructor with given Window Width, Window Height and Window Title
	Game(GLuint pWidth, GLuint pHeigth, const char* pWindowTitle);
	// Destructor
	~Game();

	// Main Game Loop
	bool gameLoop();
	// Sets window centered
	void glfwSetWindowCenter(GLFWwindow* window);

	// Getter Functions
	GLFWwindow* getWindow() const;
	GLuint getWidth() const;
	GLuint getHeight() const;
	const char* getTitle() const;

	// Setter Functions
	void setWindow(GLFWwindow* pWindow);
	void setWidth(GLuint pWidth);
	void setHeight(GLuint pHeight);
	void setTitle(const char* pTitle);

	// background color
	const static GLfloat RED;
	const static GLfloat GREEN;
	const static GLfloat BLUE;

// Variables
private:
	// Window instance
	GLFWwindow* mWindow;
	// Window width
	GLuint mWidth;
	// Window height
	GLuint mHeight;
	// Window title
	const char* mTitle;
	// Mouse Coordiantes/data
	GLfloat lastX = 400;
	GLfloat lastY = 300;
	bool firstMouse = true;
	// Time variables
	GLfloat deltaTime = 0.1f;
	GLfloat lastFrame = 0.0f;

	// Spawn
	glm::vec3 SpawnLocation;

	// Floor terrain
	Terrain* mFloor;
	// Player
	Player* mPlayer;
	// Camera object
	Camera* mCamera;
	// Skybox object
	Skybox* mSkybox;
	// Main Renderer
	MainRenderer* mRenderer;
	// Sound Engine
	irrklang::ISoundEngine* SoundEngine;

// Functions
private:
	// Callback functions
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	// Setting functions
	// Player movment
	void do_movement();
};

