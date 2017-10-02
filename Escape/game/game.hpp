#pragma once
// Inclusion of libraries

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
// Special glm functions
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
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
// Text Loader class
#include <ft2build.h>
#include FT_FREETYPE_H
// Audio class
#include <irrKlang.h>
// spot
#include "../light/spotlight.hpp"
// Terrain Generator
#include "../terrain/generator/TerrainGenerator.hpp"
#include <stdlib.h>


// Declaration of game class
class Game
{
// All public functions of the class
public:
	// Constructor with given Window Width, Window Height and Window Title
	Game(GLuint pWidth, GLuint pHeigth, const char* pWindowTitle);
	~Game();
	bool gameLoop();


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

public:
	// background color
	const static GLfloat RED;
	const static GLfloat GREEN;
	const static GLfloat BLUE;

private:
	Terrain* Boden;
	// Variables
	GLFWwindow* mWindow;
	GLuint mWidth;
	GLuint mHeight;
	const char* mTitle;
	Camera* mCamera;
	// Bool
	GLfloat lastX = 400, lastY = 300;
	GLfloat deltaTime = 0.1f;
	GLfloat lastFrame = 0.0f;
	bool firstMouse = true;

	// Player
	Player* mPlayer;
	// Main Renderer
	MainRenderer* mRenderer;
	// Sound Engine
	irrklang::ISoundEngine* SoundEngine;

	// Spawn
	glm::vec3 SpawnLocation;

	void glfwSetWindowCenter(GLFWwindow* window);


	// Functions
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void do_movement();

	void controlSound();





};

