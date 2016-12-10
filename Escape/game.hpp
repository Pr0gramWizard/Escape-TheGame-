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


	Camera* mCamera;
	// Bool
	bool keys[1024];
	GLfloat lastX = 400, lastY = 300;
	GLfloat deltaTime = 0.1f;
	GLfloat lastFrame = 0.0f;

	// Pointers to other classes
	Shader* mShader;
	bool firstMouse = true;



private:
	// Variables
	GLFWwindow* mWindow;
	GLuint mWidth;
	GLuint mHeight;
	const char* mTitle;


};

