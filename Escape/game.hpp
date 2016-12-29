#pragma once

// Inclusion of libraries

// Standard Input/Output Stream
#include <iostream>
// SOIL
#include <SOIL.h>
// GLEW
#define GLEW_STATIC
#include <glew.h>
// GLFW
#include <glfw3.h>
// Camera class
#include "camera.hpp"
// Terrain class
#include "terrain.hpp"
// Player class
#include "player.hpp"
// Loader class
#include "loader.hpp"
// Renderer class
#include "entityRenderer.hpp"
#include "terrainRenderer.hpp"
#include "mainrenderer.hpp"
// Math class
#include "math.hpp"
// List
#include <list>

#include <mat4x4.hpp>
#include <vec3.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtx\string_cast.hpp>

class Game
{
public:
	Game();
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

	
	static bool isKeyPressed(int key);


private:
	static bool keys[1024];
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



	// Functions
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void do_movement();




};

