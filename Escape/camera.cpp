#include "camera.hpp"

// Constructor with vectors
Camera::Camera()
{
	this->setPosition(Vector3D(0.0f,0.0f,0.0f));
	this->setWorldUp(Vector3D(0.0f,1.0f,0.0f));
	this->setFront(Vector3D(0.0f, 0.0f, -1.0f));
	this->setYaw(YAW);
	this->setPitch(PITCH);
	this->setMovementSpeed(SPEED);
	this->setMouseSensitivity(SENSITIVTY);
	this->setZoom(ZOOM);
	this->updateCameraVectors();
}

Camera::Camera(GLfloat pPosX, GLfloat pPosY, GLfloat pPosZ, GLfloat pUpX, GLfloat pUpY, GLfloat pUpZ, GLfloat pYaw, GLfloat pPitch) 
{
	this->setFront(Vector3D(0.0f, 0.0f, -1.0f));
	this->setMovementSpeed(SPEED);
	this->setMouseSensitivity(SENSITIVTY);
	this->setZoom(ZOOM);
	this->setPosition(Vector3D(pPosX, pPosY, pPosZ));
	this->setWorldUp(Vector3D(pUpX, pUpY, pUpZ));
	this->setYaw(pYaw);
	this->setPitch(pPitch);
	this->updateCameraVectors();
}

Matrix4D Camera::GetViewMatrix()
{
	Matrix4D matrix;
	return matrix.lookAt(this->getPosition(), this->getPosition() + this->getFront(), this->getUp());
}


void Camera::ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime)
{
	GLfloat velocity = this->getMovementSpeed() * deltaTime;

	if (pDirection == FORWARD)
		this->setPosition(this->getPosition() - (this->getFront() * velocity));
	if (pDirection == BACKWARD)
		this->setPosition(this->getPosition() + (this->getFront() * velocity));
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
	Vector3D Front;

	Front.x = cos(toRadians(this->getYaw())) * cos(toRadians(this->getPitch()));
	Front.y = sin(toRadians(this->getPitch()));
	Front.z = sin(toRadians(this->getYaw())) * cos(toRadians(this->getPitch()));

	this->setFront(Front.normalize());

	this->setRight(this->getFront().crossproduct(this->getWorldUp()).normalize());
	this->setUp(this->getRight().crossproduct(this->getFront()).normalize());

}

float Camera::toRadians(float pAngle)
{
		float PI = 3.14159265358979323846f;
		return pAngle * (PI / 180.0f);
}



Vector3D Camera::getPosition() const
{
	return mPosition;
}
Vector3D Camera::getFront() const
{
	return mFront;
}
Vector3D Camera::getUp() const
{
	return mUp;
}
Vector3D Camera::getRight() const
{
	return mRight;
}
Vector3D Camera::getWorldUp() const
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
void Camera::setPosition(Vector3D pPosition)
{
	mPosition = pPosition;
}
void Camera::setFront(Vector3D pFront)
{
	mFront = pFront;
}
void Camera::setUp(Vector3D pUp)
{
	mUp = pUp;
}
void Camera::setRight(Vector3D pRight)
{
	mRight = pRight;
}
void Camera::setWorldUp(Vector3D pWorldUp)
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