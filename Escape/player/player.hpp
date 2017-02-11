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
// String
#include <string>
// Random number
#include <random>
// Refference to the camera class
#include "../camera/camera.hpp"
// Reference to keyboard
#include "../input/keyboard.hpp"
// Maths
#include "../math/math.hpp"
// Reference to the terrain class
#include "../terrain/terrain.hpp"
// Sound Engine
#include <irrKlang.h>

// Declaration of the player class
class Player {

// Some static player settings
public:
	static const GLfloat MOVESPEED;
	static const GLfloat GRAVITY;
	static const GLfloat JUMPPOWER;
	static const GLfloat JUMP_COOLDOWN;
	static const GLfloat STRAFE_ANGLE;
	static const GLfloat Player::ANGLE_CLIMB;
		
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
	void Player::move(Terrain* pFloor, Terrain* pCeiling, float pDelta, bool pWallCollision);
	// Function to change the players position by a certain vector
	void incPosition(glm::vec3 pOffset);
	// Function to increase the player's rotation (around y-axis)
	void incRotation(GLfloat pOffsetY);
	// Jump method
	void jump();
	// Crouch method
	void crouch();

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
	void setCrouching(bool pCrouching);
	void setSprint(bool pSprint);
	void setIsBelowLake(bool pIsBelowLake);
	void setIsBurning(bool pIsBurning);

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
	bool getSprint() const;
	bool getCrouching() const;
	bool getJumping() const;
	bool isBelowLake() const;
	bool isBurning() const;
	glm::vec3 getCameraPosition() const;
	Camera* getCamera();

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
	// Bool to check if player is sprinting
	bool mSprinting;
	// Window Height
	int mWindowHeight;
	// Window Width
	int mWindowWidth;
	// true if player is below lake
	bool mIsBelowLake;
	// true if player is burning
	bool mIsBurning;
	// Player Sound (Used for walking)
	irrklang::ISoundEngine* WalkSound;
	// Cooldown for jumping
	float mJumpCooldown;

// All private functions of the class
private:
	// Sets Movement Variables
	void setMoveVariables();
	void playWalkingSound(int StepNumber);
};