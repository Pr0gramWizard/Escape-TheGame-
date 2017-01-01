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
// Maths
#include "math.hpp"
// Reference to the terrain class
#include "terrain.hpp"

// Declaration of the player class
class Player {

// Some static player settings
public:
	static const GLfloat MOVESPEED;
	static const GLfloat GRAVITY;
	static const GLfloat JUMPPOWER;
	static const GLfloat STRAFE_ANGLE;
		
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
	void move(Terrain* pTerrain, float pDelta);
	// Function to change the players position by a certain vector
	void incPosition(glm::vec3 pOffset);
	// Function to increase the player's rotation (around y-axis)
	void incRotation(GLfloat pOffsetY);
	// Jump method
	void jump();

	void crouch();

	void setCrouching(bool pCrouching);

	bool getCrouching() const;

	// Setter Functions
	void setPosition(glm::vec3 pPosition);
	void setHeight(GLfloat pHeight);
	void setStrafeAngle(GLfloat pStrafeAngle);
	void setName(const char* pName);
	void setWindowHeight(int pHeight);
	void setWindowWidth(int pWidth);
	void setYRotation(GLfloat pYRot);
	void setMovementSpeed(GLfloat pMovementSpeed);
	void setUpSpeed(GLfloat pUpSpeed);
	void setJumping(bool pJumping);

	// Getter Functions
	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	GLfloat getYRotation() const;
	bool isJumping() const;
	GLfloat getHeight() const;
	GLfloat getStrafeAngle() const;
	const char* getName() const;
	int getWindowHeight() const;
	int getWindowWidth() const;
	GLfloat getMovementSpeed() const;

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
	// Current Up Speed
	GLfloat mUpSpeed;
	// Current Strafe
	GLfloat mStrafeAngle;
	// Player name
	const char* mName;
	// Pointer to camera class
	Camera* mEye;
	// true if player is jumping
	bool mJumping;
	// true if player is crouching
	bool mCrouching;
	// Window Height
	int mWindowHeight;
	// Window Width
	int mWindowWidth;

	// Sets Movement Variables
	void setMoveVariables();
};