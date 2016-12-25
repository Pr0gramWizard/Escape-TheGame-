#include "camera.hpp"

// Constructor with vectors
Camera::Camera()
{
	this->setPosition(glm::vec3(0.0f,0.0f,-3.0f));
	this->setWorldUp(glm::vec3(0.0f,1.0f,0.0f));
	this->setFront(glm::vec3(0.0f, 0.0f, -1.0f));
	this->setYaw(YAW);
	this->setPitch(PITCH);
	this->setMovementSpeed(SPEED);
	this->setMouseSensitivity(SENSITIVTY);
	this->setZoom(ZOOM);
	this->updateCameraVectors();
}

Camera::Camera(GLfloat pPosX, GLfloat pPosY, GLfloat pPosZ, GLfloat pUpX, GLfloat pUpY, GLfloat pUpZ, GLfloat pYaw, GLfloat pPitch) 
{
	this->setFront(glm::vec3(0.0f, 0.0f, -1.0f));
	this->setMovementSpeed(SPEED);
	this->setMouseSensitivity(SENSITIVTY);
	this->setZoom(ZOOM);
	this->setPosition(glm::vec3(pPosX, pPosY, pPosZ));
	this->setWorldUp(glm::vec3(pUpX, pUpY, pUpZ));
	this->setYaw(pYaw);
	this->setPitch(pPitch);
	this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 matrix;
	return glm::lookAt(this->getPosition(), this->getPosition() + this->getFront(), this->getUp());
}

glm::mat4 Camera::GetProjectionMatrix(int pHeight, int pWidth)
{
	return glm::perspective(this->getZoom(), (float)pWidth / (float)pHeight, 0.1f, 100.0f);
}


void Camera::ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime)
{
	GLfloat velocity = this->getMovementSpeed() * deltaTime;

	if (pDirection == FORWARD)
		this->setPosition(this->getPosition() + (this->getFront() * velocity));
	if (pDirection == BACKWARD)
		this->setPosition(this->getPosition() - (this->getFront() * velocity));
	if (pDirection == LEFT)
		this->setPosition(this->getPosition() - (this->getRight() * velocity));
	if (pDirection == RIGHT)
		this->setPosition(this->getPosition() + (this->getRight() * velocity));
}

void Camera::ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset)
{
	GLboolean constrainPitch = true;

	pXOffset *= this->getMouseSensitivity();
	pYOffset *= this->getMouseSensitivity();

	this->setYaw(this->getYaw() + pXOffset);
	this->setPitch(this->getPitch() + pYOffset);

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

}

void Camera::ProcessMouseScroll(GLfloat pYOffset)
{
	if (this->getZoom() >= 1.0f && this->getZoom() <= 45.0f)
		this->setZoom(this->getZoom() - pYOffset);
	if (this->getZoom() <= 1.0f)
		this->setZoom(1.0f);
	if (this->getZoom() >= 45.0f)
		this->setZoom(45.0f);
}



void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->getYaw())) * cos(glm::radians(this->getPitch()));
	front.y = sin(glm::radians(this->getPitch()));
	front.z = sin(glm::radians(this->getYaw())) * cos(glm::radians(this->getPitch()));
	this->setFront(glm::normalize(front));
	// Also re-calculate the Right and Up vector
	this->setRight(glm::normalize(glm::cross(this->getFront(), this->getWorldUp())));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->setUp(glm::normalize(glm::cross(this->getRight(), this->getFront())));

}

float Camera::toRadians(float pAngle)
{
		float PI = 3.14159265358979323846f;
		return pAngle * (PI / 180.0f);
}



glm::vec3 Camera::getPosition() const
{
	return mPosition;
}
glm::vec3 Camera::getFront() const
{
	return mFront;
}
glm::vec3 Camera::getUp() const
{
	return mUp;
}
glm::vec3 Camera::getRight() const
{
	return mRight;
}
glm::vec3 Camera::getWorldUp() const
{
	return mWorldUp;
}
GLfloat Camera::getYaw() const
{
	return mYaw;
}
GLfloat Camera::getPitch() const
{
	return mPitch;
}
GLfloat Camera::getMovementSpeed() const
{
	return mMovementSpeed;
}
GLfloat Camera::getMouseSensitivity() const
{
	return mMouseSensitivity;
}
GLfloat Camera::getZoom() const
{
	return mZoom;
}
void Camera::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
	mPosition.y = 1.0f;
}
void Camera::setFront(glm::vec3 pFront)
{
	mFront = pFront;
}
void Camera::setUp(glm::vec3 pUp)
{
	mUp = pUp;
}
void Camera::setRight(glm::vec3 pRight)
{
	mRight = pRight;
}
void Camera::setWorldUp(glm::vec3 pWorldUp)
{
	mWorldUp = pWorldUp;
}
void Camera::setYaw(GLfloat pYaw)
{
	mYaw = pYaw;
}
void Camera::setPitch(GLfloat pPitch)
{
	mPitch = pPitch;
}
void Camera::setMovementSpeed(GLfloat pMovementSpeed)
{
	mMovementSpeed = pMovementSpeed;
}
void Camera::setMouseSensitivity(GLfloat pMouseSensitivity)
{
	mMouseSensitivity = pMouseSensitivity;
}
void Camera::setZoom(GLfloat pZoom)
{
	mZoom = pZoom;
}