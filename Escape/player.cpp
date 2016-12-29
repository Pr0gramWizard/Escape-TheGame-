// Inclusion of the declaration of the class
#include "player.hpp"

// Defintion of the global player constants
const GLfloat Player::MOVESPEED = 15;
const GLfloat Player::GRAVITY = -50;
const GLfloat Player::JUMPPOWER = 20;
const GLfloat Player::STRAFE_ANGLE = 90;

// Default Constructor
Player::Player(glm::vec3 pPosition, GLfloat pHeight, const char * pName, int pWindowHeight, int pWindowWidth)
{
	this->setPosition(pPosition);
	this->setHeight(pHeight);
	this->setName(pName);
	this->setMovementSpeed(0);
	this->setUpSpeed(0);
	this->setStrafeAngle(0);
	this->setWindowHeight(pWindowHeight);
	this->setWindowWidth(pWindowWidth);
	// Creating new instance of the camera class
	mEye = new Camera();
}

// Default Destructor
Player::~Player()
{
	// Destroying the pointer to the camera class
	delete mEye;
}

// Function to move the player	
void Player::move(Terrain* pTerrain, float pDelta)
{
	this->setMoveVariables();
	float yRotation = mYRot;
	// dPos is the distance the player is going to move
	float dPos = mMovementSpeed * pDelta;
	float dx = dPos * sin(Math::toRadians(yRotation + this->getStrafeAngle()));
	float dz = dPos * cos(Math::toRadians(yRotation + this->getStrafeAngle()));
	this->incPosition(glm::vec3(dx, 0, dz));
	mUpSpeed += Player::GRAVITY * pDelta;
	this->incPosition(glm::vec3(0, mUpSpeed * pDelta, 0));

	float terrainHeight = pTerrain->getHeight(mPosition.x, mPosition.z);
	if (getPosition().y < terrainHeight) {
		this->setUpSpeed(0);
		this->setJumping(false);
		mPosition.y = terrainHeight;
	}

	// Set camera's new position
	mEye->setPosition(this->getPosition() + glm::vec3(0, this->getHeight(), 0));
}

// Function to change players position by a given offset vector
void Player::incPosition(glm::vec3 pOffset)
{
	mPosition.x += pOffset.x;
	mPosition.y += pOffset.y;
	mPosition.z += pOffset.z;
}

void Player::incRotation(GLfloat pOffsetY)
{
	mYRot += pOffsetY;
}

void Player::jump()
{
	if (!this->isJumping())
	{
		this->setJumping(true);
		this->setUpSpeed(Player::JUMPPOWER);
	}
}

// Setting the players position to a given point
void Player::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

// Setting the players height to a given value
void Player::setHeight(GLfloat pHeight)
{
	mHeight = pHeight;
}

void Player::setStrafeAngle(GLfloat pStrafeAngle)
{
	mStrafeAngle = pStrafeAngle;
}

// Setting the players name
void Player::setName(const char * pName)
{
	mName = pName;
}

// Setting the window height
void Player::setWindowHeight(int pHeight)
{
	mWindowHeight = pHeight;
}

// Setting the window width
void Player::setWindowWidth(int pWidth)
{
	mWindowWidth = pWidth;
}

// Setting the players movement speed
void Player::setMovementSpeed(GLfloat pMovementSpeed)
{
	mMovementSpeed = pMovementSpeed;
}

void Player::setUpSpeed(GLfloat pUpSpeed)
{
	mUpSpeed = pUpSpeed;
}

void Player::setJumping(bool pJumping)
{
	mJumping = pJumping;
}

// Returns the current position of the player
glm::vec3 Player::getPosition() const
{
	return mPosition;
}

glm::vec3 Player::getRotation() const
{
	return glm::vec3(0, mYRot, 0);
}

bool Player::isJumping() const
{
	return mJumping;
}

// Returns the current height of the player
GLfloat Player::getHeight() const
{
	return mHeight;
}

GLfloat Player::getStrafeAngle() const
{
	return mStrafeAngle;
}

// Returns the name of the player
const char * Player::getName() const
{
	return mName;
}

// Returns the window height
int Player::getWindowHeight() const
{
	return mWindowHeight;
}

// Returns the window width
int Player::getWindowWidth() const
{
	return mWindowWidth;
}

// Returns the current view vector of the player
glm::vec3 Player::getViewVector() const
{
	return mEye->getFront();
}

// Returns the current movement speed of the player
GLfloat Player::getMovementSpeed() const
{
	return mMovementSpeed;
}

// Returns the current ViewMatrix
glm::mat4 Player::getViewMatrix() const
{
	return mEye->GetViewMatrix();
}

// Returns the current ProjectionsMatrix
glm::mat4 Player::getProjectionMatrix() const
{
	return mEye->GetProjectionMatrix(this->getWindowHeight(),this->getWindowWidth());
}

// Processes the keyboard input by the user
void Player::ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime)
{
	mEye->ProcessKeyboard(pDirection, deltaTime);
}

// Processes the Mouse input by the user
void Player::ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset,GLfloat deltaTime)
{
	mYRot = mEye->ProcessMouseMovement(pXOffset, pYOffset, deltaTime) - 90.0f;
}

// Processes the Scroll Wheel input by the user
void Player::ProcessMouseScroll(GLfloat pYOffset)
{
	mEye->ProcessMouseScroll(pYOffset);
}

void Player::setMoveVariables()
{
	if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
		this->setMovementSpeed(Player::MOVESPEED);
	}
	else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
		this->setMovementSpeed(-Player::MOVESPEED);
	}
	else 
	{
		this->setMovementSpeed(0);
	}

	// implement strafing
	if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
		this->setMovementSpeed(Player::MOVESPEED);
		this->setStrafeAngle(Player::STRAFE_ANGLE);
	}
	else if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
		this->setMovementSpeed(Player::MOVESPEED);
		this->setStrafeAngle(-Player::STRAFE_ANGLE);
	}
	else 
	{
		this->setStrafeAngle(0);
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_SPACE)) {
		this->jump();
	}
}
