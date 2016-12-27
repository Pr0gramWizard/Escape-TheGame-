#pragma once
// Inclusion of every library
// OpenGLMath 
#include <glm.hpp>
// OpenGLExtensionWrangler
#include <glew.h>
// 4x4 Matrix
#include <mat4x4.hpp>
// 3x1 Vector
#include <vec3.hpp>
// Refference to the camera class
#include "camera.hpp"

// Declaration of the player class
class Player {

// Some static player settings
public:
	static const GLfloat MOVESPEED;
	static const GLfloat TURNSPEED;
	static const GLfloat GRAVITY;
	static const GLfloat JUMPPOWER;
		
// All public functions
public:
	// Default Constructor:
	// > pPosition: The position where the player should spawn
	// > pName:		Player name
	// > 
	Player(glm::vec3 pPosition, GLfloat pHeight, const char* pName, int pWindowHeight, int pWindowWidth);

	void move();

	//adds offset to position
	void incPosition(glm::vec3 pOffset);
	//sets position to absolute value
	void setPosition(glm::vec3 pPosition);
	void setHeight(GLfloat pHeight);
	void setName(const char* pName);
	void setWindowHeight(int pHeight);
	void setWindowWidht(int pWidth);

	glm::vec3 getPosition() const;
	GLfloat getHeight() const;
	const char* getName() const;
	int getWindowHeight() const;
	int getWindowWidht() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getViewVector() const;
	void ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset,GLfloat deltaTime);
	void ProcessMouseScroll(GLfloat pYOffset);

private:
	glm::vec3 mPosition;
	//used for camera position and collision
	GLfloat mHeight;
	GLfloat mCurrentMoveSpeed;
	GLfloat mCurrentTurnSpeed;
	//add vec3 viewDirection?
	const char* mName;
	Camera* mEye;
	int mWindowHeight;
	int mWindowWidth;
};