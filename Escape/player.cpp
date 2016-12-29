// Inclusion of the declaration of the class
#include "player.hpp"

// Defintion of the global player constants
const GLfloat Player::MOVESPEED = 10;
const GLfloat Player::GRAVITY = -90;
const GLfloat Player::JUMPPOWER = 45;

// Default Constructor
Player::Player(glm::vec3 pPosition, GLfloat pHeight, const char * pName, int pWindowHeight, int pWindowWidth)
{
	setPosition(pPosition);
	setHeight(pHeight);
	setName(pName);
	setMovementSpeed(0);
	setUpSpeed(0);
	setWindowHeight(pWindowHeight);
	setWindowWidth(pWindowWidth);
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
void Player::move(float pDelta)
{
	setMoveVariables();
	float yRotation = mYRot;
	// dPos is the distance the player is going to move
	float dPos = mMovementSpeed * pDelta;
	float dx = dPos * sin(Math::toRadians(yRotation));
	float dz = dPos * cos(Math::toRadians(yRotation));
	incPosition(glm::vec3(dx, 0, dz));
	mUpSpeed += Player::GRAVITY * pDelta;
	incPosition(glm::vec3(0, mUpSpeed, 0));

	// Replace 0 with terrain height at players position
	if (getPosition().y < 0) {
		setUpSpeed(0);
		mPosition.y = 0;
	}

	// Set camera's new position
	mEye->setPosition(getPosition()+glm::vec3(0,getHeight(), 0));
	// TODO set camera's new rotation
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

// Returns the current position of the player
glm::vec3 Player::getPosition() const
{
	return mPosition;
}

glm::vec3 Player::getRotation() const
{
	return glm::vec3(0, mYRot, 0);
}

// Returns the current height of the player
GLfloat Player::getHeight() const
{
	return mHeight;
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
		mMovementSpeed = Player::MOVESPEED;
	}
	else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
		mMovementSpeed = -Player::MOVESPEED;
	}
	else {
		mMovementSpeed = 0;
	}

	// implement strafing
	if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
	}
	else if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
	}
	else {
	}
}
