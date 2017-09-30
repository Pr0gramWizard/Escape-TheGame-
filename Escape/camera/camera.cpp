#include "camera.hpp"

// Default Constructor
// Sets the Camera to the position (0,0,-3)
Camera::Camera()
{
	this->setPosition(glm::vec3(0.0f,1.0f,3.0f));
	this->setWorldUp(glm::vec3(0.0f,1.0f,0.0f));
	this->setFront(glm::vec3(0.5f, 0.5f, -1.0f));
	this->setYaw(YAW);
	this->setPitch(PITCH);
	this->setMovementSpeed(SPEED);
	this->setMouseSensitivity(SENSITIVTY);
	this->setFov(FOV);
	this->updateCameraVectors();
}

// Constructor with given position and up vector
Camera::Camera(glm::vec3 pPosition, glm::vec3 pUp, GLfloat pYaw, GLfloat pPitch) 
{
	this->setFront(glm::vec3(0.0f, 0.0f, -1.0f));
	this->setMovementSpeed(SPEED);
	this->setMouseSensitivity(SENSITIVTY);
	this->setFov(FOV);
	this->setPosition(pPosition);
	this->setWorldUp(pUp);
	this->setYaw(pYaw);
	this->setPitch(pPitch);
	this->updateCameraVectors();
}

// Returns the current View Matrix
glm::mat4 Camera::GetViewMatrix()
{
	mViewMatrix = glm::lookAt(this->getPosition(), this->getPosition() - this->getFront(), this->getUp());

	return mViewMatrix;
}

void Camera::setViewMatrix(glm::mat4 pMatrix) {
	mViewMatrix = pMatrix;
}

// Returns the current Projection Matrix
glm::mat4 Camera::GetProjectionMatrix(int pHeight, int pWidth)
{
	// Using perspective function
	return glm::perspective(this->getFov(), (float)pWidth / (float)pHeight, 0.1f, 1000.0f);
}

// Process the Keyboard input based on the curreent deltaTime
void Camera::ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime)
{
	GLfloat velocity = this->getMovementSpeed() * deltaTime;

	if (pDirection == FORWARD)
		this->setPosition(this->getPosition() - (this->getFront() * velocity));
	if (pDirection == BACKWARD)
		this->setPosition(this->getPosition() + (this->getFront() * velocity));
	if (pDirection == LEFT)
		this->setPosition(this->getPosition() + (this->getRight() * velocity));
	if (pDirection == RIGHT)
		this->setPosition(this->getPosition() - (this->getRight() * velocity));
}

// Process the Mouse input based on X/Y Offset of the mouse
GLfloat Camera::ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset, GLfloat deltaTime)
{
	GLboolean constrainPitch = true;

	pXOffset *= (this->getMouseSensitivity() * 200) * deltaTime;
	pYOffset *= (this->getMouseSensitivity() * 200) * deltaTime;

	this->setYaw(this->getYaw() - pXOffset);
	this->setPitch(this->getPitch() - pYOffset);

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->getPitch() > 89.0f)
			this->setPitch(89.0f);
		if (this->getPitch() < -89.0f)
			this->setPitch(-89.0f);
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();

	return this->getYaw();
}

// Process Mouse Scroll input
void Camera::ProcessMouseScroll(GLfloat pYOffset)
{
	if (this->getFov() >= 1.0f && this->getFov() <= 45.0f)
		this->setFov(this->getFov() - pYOffset);
	if (this->getFov() <= 1.0f)
		this->setFov(1.0f);
	if (this->getFov() >= 45.0f)
		this->setFov(45.0f);
}

// Updating all the vector acording to euler angles and given laws
void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->getYaw())) * cos(glm::radians(this->getPitch()));
	front.y = sin(glm::radians(this->getPitch()));
	front.z = -(sin(glm::radians(this->getYaw())) * cos(glm::radians(this->getPitch())));
	this->setFront(glm::normalize(front));
	// Also re-calculate the Right and Up vector
	this->setRight(glm::normalize(glm::cross(this->getFront(), this->getWorldUp())));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->setUp(glm::normalize(glm::cross(this->getRight(), this->getFront())));

}

// Convert an angle from degree to radian
float Camera::toRadians(float pAngle)
{
		float PI = 3.14159265358979323846f;
		return pAngle * (PI / 180.0f);
}


// Returns the current position of the camera
glm::vec3 Camera::getPosition() const
{
	return mPosition;
}
// Returns the current Front vector
glm::vec3 Camera::getFront() const
{
	return mFront;
}
// Returns the current Up vector
glm::vec3 Camera::getUp() const
{
	return mUp;
}
// Returns the current Right vector
glm::vec3 Camera::getRight() const
{
	return mRight;
}
// Returns the current WorldUp vector
glm::vec3 Camera::getWorldUp() const
{
	return mWorldUp;
}
// Returns the current Yaw value
GLfloat Camera::getYaw() const
{
	return mYaw;
}
// Returns the current Pitch value
GLfloat Camera::getPitch() const
{
	return mPitch;
}
// Returns the current Movement Speed
GLfloat Camera::getMovementSpeed() const
{
	return mMovementSpeed;
}
// Returns the current Mouse Sensitivity
GLfloat Camera::getMouseSensitivity() const
{
	return mMouseSensitivity;
}
// Returns the current FieldOfView
GLfloat Camera::getFov() const
{
	return mFov;
}
// Sets the camera position based on a given vector
void Camera::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
	// Camera always stays at y = 0.5f
	// mPosition.y = 3.0f;
}
// Sets the front vector based on a given vector
void Camera::setFront(glm::vec3 pFront)
{
	mFront = pFront;
}
// Sets the up vector based on a given vector
void Camera::setUp(glm::vec3 pUp)
{
	mUp = pUp;
}
// Sets the right vector based on a given vector
void Camera::setRight(glm::vec3 pRight)
{
	mRight = pRight;
}
// Sets the world up vector based on a given vector
void Camera::setWorldUp(glm::vec3 pWorldUp)
{
	mWorldUp = pWorldUp;
}
// Sets the Yaw based on a given value
void Camera::setYaw(GLfloat pYaw)
{
	mYaw = pYaw;
}
// Sets the Pitch based on a given value
void Camera::setPitch(GLfloat pPitch)
{
	mPitch = pPitch;
}
// Sets the movement speed based on a given value
void Camera::setMovementSpeed(GLfloat pMovementSpeed)
{
	mMovementSpeed = pMovementSpeed;
}
// Sets the mouse sensitivity based on a given value
void Camera::setMouseSensitivity(GLfloat pMouseSensitivity)
{
	mMouseSensitivity = pMouseSensitivity;
}
// Sets the FieldOfView based on a given value
void Camera::setFov(GLfloat pFov)
{
	mFov = pFov;
}
// Increases the Y-Position of the camera
void Camera::incYPosition(GLfloat pY)
{
	mPosition.y += pY;
}
// Inverts the pitch of the camera
void Camera::invertPitch()
{
	mPitch = -mPitch;
	this->updateCameraVectors();
}
