// Inclusion of the declaration of the class
#include "player.hpp"

// Defintion of the global player constants
const GLfloat Player::MOVESPEED = 7;
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
	this->setCrouching(false);
	this->setWindowHeight(pWindowHeight);
	this->setWindowWidth(pWindowWidth);
	// Creating new instance of the camera class
	mEye = new Camera();
	this->setYRotation(mEye->getYaw() - 90.0f);
	WalkSound = irrklang::createIrrKlangDevice();

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
	float yRotation = this->getYRotation();
	// dPos is the distance the player is going to move
	float dPos = mMovementSpeed * pDelta;
	
	// play walk sound if needed
	if (dPos != 0 && !mJumping) {
		if (!WalkSound->isCurrentlyPlaying("audio/walk.mp3")) {
			WalkSound->play2D("audio/walk.mp3", GL_FALSE);
		}
	}
	else {
		WalkSound->stopAllSounds();
	}

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

void Player::crouch()
{
	if (!this->getCrouching()) {
		this->setCrouching(true);
		this->setHeight(this->getHeight() / 2.0f);
	}
}

void Player::setCrouching(bool pCrouching)
{
	mCrouching = pCrouching;
}

bool Player::getCrouching() const
{
	return mCrouching;
}

void Player::setSprint(bool pSprint)
{
	mSprinting = pSprint;
}

bool Player::getSprint() const
{
	return mSprinting;
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

// Setting rotation around y-axis
void Player::setYRotation(GLfloat pYRot)
{
	mYRot = pYRot;
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

GLfloat Player::getYRotation() const
{
	return mYRot;
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

glm::vec3 Player::getCameraPosition() const
{
	return mEye->getPosition();
}

Camera* Player::getCamera()
{
	return mEye;
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
	/*
	* 0: no move
	* 1: moving forward
	* -1: moving backwards
	*/
	int movingMode = 0;
	
	/*
	* 1: no crouching
	* 2: crouching
	*/
	int crouchingMode = 1;
	if (this->getCrouching())
	{
		crouchingMode = 2;
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
		if (this->getSprint())
		{
			this->setMovementSpeed(Player::MOVESPEED * 3);
			movingMode = 1;
			this->setSprint(false);
		}
		else {
			this->setMovementSpeed(Player::MOVESPEED / crouchingMode);
			movingMode = 1;
		}

		// WalkSound->play2D("audio/walk.mp3", GL_FALSE);
	}
	else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
		movingMode = -1;
		this->setMovementSpeed(-Player::MOVESPEED / crouchingMode);
	}
	else
	{
		this->setMovementSpeed(0);
	}

	// implement strafing
	if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
		if (movingMode != 0)
		{
			this->setStrafeAngle(movingMode * Player::STRAFE_ANGLE / 2);
		}
		else
		{
			this->setMovementSpeed(Player::MOVESPEED / crouchingMode);
			this->setStrafeAngle(Player::STRAFE_ANGLE);
		}
	}
	else if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
		if (movingMode != 0)
		{
			this->setStrafeAngle(-movingMode * Player::STRAFE_ANGLE / 2);
		}
		else
		{
			this->setMovementSpeed(Player::MOVESPEED / crouchingMode);
			this->setStrafeAngle(-Player::STRAFE_ANGLE);
		}
	}
	else 
	{
		this->setStrafeAngle(0);
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_SPACE)) 
	{
		this->jump();
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_LEFT_CONTROL)) 
	{
		this->crouch();
	}
	else 
	{
		if (this->getCrouching()) 
		{
			this->setCrouching(false);
			this->setHeight(this->getHeight() * 2.0f);
		}
	}
}
