// Inclusion of the declaration of the class
#include "player.hpp"


const GLfloat Player::MOVESPEED = 5.0f;
const GLfloat Player::STRAFEANGLE = 45.0f;
const GLfloat Player::JUMPCOOLDOWN = 0.5f;

// Default Constructor
Player::Player(glm::vec3 pPosition, GLfloat pHeight, const char * pName, int pWindowHeight, int pWindowWidth)
{
	// Setting all the player variables
	this->setPosition(pPosition);
	this->setHeight(pHeight);
	this->setName(pName);
	this->setMovementSpeed(0);
	this->setUpSpeed(0);
	this->setStrafeAngle(0);
	this->setCrouching(false);
	this->setWindowHeight(pWindowHeight);
	this->setWindowWidth(pWindowWidth);
	this->setIsBelowLake(false);
	this->setIsBurning(false);
	this->setGravity(-30.0f);
	this->setJumpPower(6.0f);
	this->setJumpCooldown(0.4f);
	this->setStrafeAngle(45.0f);
	this->setClimbAngle(0.65f);
	this->setIsFlying(false);

	// Creating new instance of the camera class
	mEye = new Camera();
	this->setYRotation(mEye->getYaw() - 90.0f);
	// Create new sound engine
	WalkSound = irrklang::createIrrKlangDevice();

}

// Default Destructor
Player::~Player()
{
	// Destroying the pointer to the camera class
	delete mEye;
	// Destroying the pointer to the sound engine
	delete WalkSound;
}


// Plays a random walking sound (based on random number)
void Player::playWalkingSound(int StepNumber)
{
	// All walkings sounds are named stepX where X represents a number between [1,4]
	std::string FilePath = "audio/walking/step";
	FilePath += std::to_string(StepNumber);
	FilePath += ".wav";
	// After we created the file path with the random number we let it play (but only if there is no other song playing)
	if (!WalkSound->isCurrentlyPlaying("audio/walking/step1.wav") && !WalkSound->isCurrentlyPlaying("audio/walking/step2.wav") && !WalkSound->isCurrentlyPlaying("audio/walking/step3.wav") && !WalkSound->isCurrentlyPlaying("audio/walking/step4.wav")) {
		// Plays the sound
		WalkSound->play2D(FilePath.c_str(), GL_FALSE);
		// Log of the sound that is currently played
		// std::cout << FilePath.c_str() << std::endl;
	}
}

// Function to move the player	
void Player::move(Terrain* pFloor,Terrain* pCeiling,float pDelta, bool pWallCollision)
{

	
	// Handle jump cooldown
	this->mJumpCooldown -= pDelta;
	if (this->mJumpCooldown < 0.0f) {
		this->mJumpCooldown = 0.0f;
	}

	// Calculating the new moving variables
	this->setMoveVariables();
	// Remember to include the Y Rotation of the player
	float yRotation = this->getYRotation();
	// The length (in units) the player is moving
	float dPos = mMovementSpeed * pDelta;

	// The Length the player is going in X direction
	float dx = dPos * sin(Math::toRadians(yRotation + this->getStrafeAngle()));
	// The Length the player is going in Z direction
	float dz = dPos * cos(Math::toRadians(yRotation + this->getStrafeAngle()));
	// Updating the players position
	this->incPosition(glm::vec3(dx, 0, dz));

	//**** Collision detection ****
	glm::vec3 input;
	glm::vec3 normal;
	// tune this to "fudge" the "push away" from the wall
	float bounceFudge = 1.01f;


	// floor collision
	float terrainHeight;
	float nextTerrainHeight = pFloor->getHeight(mPosition.x, mPosition.z);
	float angle = atan((nextTerrainHeight - mPosition.y)/sqrt(dx * dx + dz * dz));
	normal = pFloor->getNormalAt(mPosition.x, mPosition.z);
	float normalDot = glm::dot(normal, glm::vec3(0, 1, 0));
	if (angle > 0 && normalDot < this->getClimbAngle()) {
		this->incPosition(glm::vec3(-dx, 0, -dz));
		input = glm::vec3(dx, 0.0f, dz);

		// normalize input, but keep track of original size
		float inputLength = glm::length(input);
		input = input * glm::vec3(1.0f / inputLength);

		// only user x and z component of normal
		normal = glm::normalize(glm::vec3(normal.x, 0.0f, normal.z));

		float dot = glm::dot(input, normal);
		glm::vec3 intoWall = normal * glm::vec3(dot);
		intoWall = intoWall * glm::vec3(bounceFudge);

		glm::vec3 alongWall = glm::normalize(input - intoWall);
		alongWall = alongWall * glm::vec3(inputLength);

		glm::vec3 OldPosition = this->getPosition();

		this->incPosition(alongWall);

		bool invalidPosition = this->getPosition().x != this->getPosition().x || this->getPosition().y != this->getPosition().y || this->getPosition().z != this->getPosition().z;

		if (invalidPosition)
		{
			this->setPosition(OldPosition);
		}

		terrainHeight = pFloor->getHeight(mPosition.x, mPosition.z);
		WalkSound->stopAllSounds();
	}
	else {
		terrainHeight = nextTerrainHeight;
	}

	//**** END collision detection ****

	if (this->isBelowLake()) {
		mUpSpeed += this->getGravity()/1.50f * pDelta;
	}
	else {
		mUpSpeed += this->getGravity() * pDelta;
	}

	this->incPosition(glm::vec3(0, mUpSpeed * pDelta, 0));
	if (getPosition().y < terrainHeight) {
		this->setUpSpeed(0);
		this->setJumping(false);
		mPosition.y = terrainHeight;
	}
	else
	{
		mPosition.y = mPosition.y;
	}
	

	// Set camera's new position
	mEye->setPosition(this->getPosition() + glm::vec3(0, this->getHeight(), 0));

}

// Sets the important moving variables
void Player::setMoveVariables()
{
	/*
	* 0: no move
	* 1: moving forward
	* -1: moving backwards
	* 2: flying
	*/
	int movingMode = 0;

	/*
	* 1: no crouching
	* 2: crouching
	*/
	int crouchingMode = 1;
	if (Keyboard::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		this->setSprint(true);
	}

	if (this->getCrouching())
	{
		crouchingMode = 2;
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
		if (this->getSprint())
		{
			this->setMovementSpeed(Player::MOVESPEED * 1.5f);
			movingMode = 1;
			this->setSprint(false);
		}
		else if (this->isFlying()) {
			this->setMovementSpeed(Player::MOVESPEED * 2.0f);
			movingMode = 2;
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
			this->setStrafeAngle(movingMode * Player::STRAFEANGLE / 2);
		}
		else
		{
			this->setMovementSpeed(Player::MOVESPEED / crouchingMode);
			this->setStrafeAngle(Player::STRAFEANGLE);
		}
	}
	else if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
		if (movingMode != 0)
		{
			this->setStrafeAngle(-movingMode * Player::STRAFEANGLE / 2);
		}
		else
		{
			this->setMovementSpeed(Player::MOVESPEED / crouchingMode);
			this->setStrafeAngle(-Player::STRAFEANGLE);
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

	if (this->isBelowLake())
	{
		this->setMovementSpeed(this->getMovementSpeed() / 2.0f);
	}
}


// Function to change players position by a given offset vector
void Player::incPosition(glm::vec3 pOffset)
{
	mPosition.x += pOffset.x;
	mPosition.y += pOffset.y;
	mPosition.z += pOffset.z;
}

// Increasing the player Rotation
void Player::incRotation(GLfloat pOffsetY)
{
	mYRot += pOffsetY;
}

// Jump function
void Player::jump()
{
	if (!this->isJumping())
	{
		if (this->mJumpCooldown <= 0.0f) {
			this->setJumping(true);
			this->setUpSpeed(this->getJumpPower());
			this->mJumpCooldown = Player::JUMPCOOLDOWN;
		}	
	}
}

// Crouch function
void Player::crouch()
{
	if (!this->getCrouching()) {
		this->setCrouching(true);
		this->setHeight(this->getHeight() / 2.0f);
	}
}

// Sets the crouch bool
void Player::setCrouching(bool pCrouching)
{
	mCrouching = pCrouching;
}

// Returns the crouch status
bool Player::getCrouching() const
{
	return mCrouching;
}

// Returns the jumping status
bool Player::getJumping() const
{
	return mJumping;
}

// Return if the player is underwater
bool Player::isBelowLake() const
{
	return this->mIsBelowLake;
}

bool Player::isBurning() const
{
	return mIsBurning;
}

bool Player::isFlying() const
{
	return mIsFlying;
}

// Sets the sprint bool
void Player::setIsFlying(bool pFlying)
{
	mIsFlying = pFlying;
}

// Sets the sprint bool
void Player::setSprint(bool pSprint)
{
	mSprinting = pSprint;
}

// Sets the underwater bool
void Player::setIsBelowLake(bool pIsBelowLake)
{
	this->mIsBelowLake = pIsBelowLake;
}

void Player::setIsBurning(bool pIsBurning)
{
	mIsBurning = pIsBurning;
}

// Returns the sprint status
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

// Sets the strafe angle of the player
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

// Sets the Up speed of the camera
void Player::setUpSpeed(GLfloat pUpSpeed)
{
	mUpSpeed = pUpSpeed;
}

// Sets the jump bool
void Player::setJumping(bool pJumping)
{
	mJumping = pJumping;
}

// Returns the current position of the player
glm::vec3 Player::getPosition() const
{
	return mPosition;
}

// Returns the players rotation
glm::vec3 Player::getRotation() const
{
	return glm::vec3(0, mYRot, 0);
}

// Returns the player jumping status
bool Player::isJumping() const
{
	return mJumping;
}

// Returns the current height of the player
GLfloat Player::getHeight() const
{
	return mHeight;
}

// Returns the strafe angle of the player
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

// Returns the Y Rotation of the player
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

// Returns the current camera position
glm::vec3 Player::getCameraPosition() const
{
	return mEye->getPosition();
}

// Returns the pointer to the camera class
Camera* Player::getCamera()
{
	return mEye;
}

GLfloat Player::getGravity() const
{
	return mGravity;
}

GLfloat Player::getJumpPower() const
{
	return mJumpPower;
}

GLfloat Player::getJumpCooldown() const
{
	return mJumpCooldown;
}

GLfloat Player::getClimbAngle() const
{
	return mClimbAngle;
}

void Player::setGravity(GLfloat pGravity)
{
	mGravity = pGravity;
}

void Player::setJumpPower(GLfloat pJumpPower)
{
	mJumpPower = pJumpPower;
}

void Player::setJumpCooldown(GLfloat pJumpCooldown)
{
	mJumpCooldown = pJumpCooldown;
}

void Player::setClimbAngle(GLfloat pClimbAngle)
{
	mClimbAngle = pClimbAngle;
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

