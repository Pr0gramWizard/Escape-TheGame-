#pragma once
// Inclusion of every library
// OpenGLMath 
#include <glm.hpp>
// OpenGLExtensionWrangler
#include <glew.h>
// GLFW
#include <glfw3.h>
// 4x4 Matrix
#include <mat4x4.hpp>
// 3x1 Vector
#include <vec3.hpp>
// Refference to the camera class
#include "camera.hpp"
// Reference to keyboard
#include "keyboard.hpp"

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
	// > pPosition:		The position where the player should spawn
	// > pName:			Player name
	// > pWindowHeight:	Window Height
	// > pWindowWidth:	Window Width
	Player(glm::vec3 pPosition, GLfloat pHeight, const char* pName, int pWindowHeight, int pWindowWidth);
	// Default Destructor
	~Player();

	// Function to move the player
	void move();
	// Function to change the players position by a certain vector
	void incPosition(glm::vec3 pOffset);
	void incRotation(GLfloat pOffsetY);

	// Setter Functions
	void setPosition(glm::vec3 pPosition);
	void setHeight(GLfloat pHeight);
	void setName(const char* pName);
	void setWindowHeight(int pHeight);
	void setWindowWidth(int pWidth);
	void setMovementSpeed(GLfloat pMovementSpeed);
	void setTurnSpeed(GLfloat pTurnSpeed);

	// Getter Functions
	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	GLfloat getHeight() const;
	const char* getName() const;
	int getWindowHeight() const;
	int getWindowWidth() const;
	GLfloat getMovementSpeed() const;
	GLfloat getTurnSpeed() const;

	// Important World Settings
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getViewVector() const;

	// Functions to process the users input
	void ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset,GLfloat deltaTime);
	void ProcessMouseScroll(GLfloat pYOffset);

// All private member of the class
private:
	// Player position
	glm::vec3 mPosition;
	// Player rotation
	GLfloat mYRot;
	// Current Player height
	GLfloat mHeight;
	// Current Movement Speed
	GLfloat mMovementSpeed;
	// Current TurnSpeed
	GLfloat mTurnSpeed;
	// Player name
	const char* mName;
	// Pointer to camera class
	Camera* mEye;
	// Window Height
	int mWindowHeight;
	// Window Width
	int mWindowWidth;

	// Sets Movement Variables
	void setMoveVariables();
};