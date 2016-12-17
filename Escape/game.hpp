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
// Shader class
#include "shader.hpp"
// Vector 3D class
#include "vector3D.hpp"
// Matrix 4D class
#include "matrix4D.hpp"
// Camera class
#include "camera.hpp"


class Game
{
public:
	Game();
	Game(GLuint pWidth, GLuint pHeigth, const char* pWindowTitle);
	~Game();
	void prepareScene();
	void drawScene();
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





private:
	// Variables
	GLFWwindow* mWindow;
	GLuint mWidth;
	GLuint mHeight;
	const char* mTitle;
	Camera* mCamera;
	// Bool
	bool keys[1024];
	GLfloat lastX = 400, lastY = 300;
	GLfloat deltaTime = 0.1f;
	GLfloat lastFrame = 0.0f;
	bool firstMouse = true;

	// Pointers to other classes
	Shader* mShader;



	// Functions
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void do_movement();




};
