#include "player.hpp"

const GLfloat Player::MOVESPEED = 10;
const GLfloat Player::TURNSPEED = 180;
const GLfloat Player::GRAVITY = -90;
//needed?
const GLfloat Player::JUMPPOWER = 45;

Player::Player(glm::vec3 pPosition, GLfloat pHeight, const char * pName, int pWindowHeight, int pWindowWidth)
{
	setPosition(pPosition);
	setHeight(pHeight);
	setName(pName);
	mCurrentMoveSpeed = 0;
	mCurrentTurnSpeed = 0;
	setWindowHeight(pWindowHeight);
	setWindowWidht(pWindowWidth);
	mEye = new Camera(this->getPosition().x, this->getPosition().y, this->getPosition().z, 0.0f, 1.0f, 0.0f, -90.0f, 0.0f);
}

void Player::move()
{
	//apply gravity
	/* TODO */

	//collision dectection with terrain
	/* TODO */
}

void Player::incPosition(glm::vec3 pOffset)
{
	mPosition.x += pOffset.x;
	mPosition.y += pOffset.y;
	mPosition.z += pOffset.z;
}

void Player::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

void Player::setHeight(GLfloat pHeight)
{
	mHeight = pHeight;
}

void Player::setName(const char * pName)
{
	mName = pName;
}

void Player::setWindowHeight(int pHeight)
{
	mWindowHeight = pHeight;
}

void Player::setWindowWidht(int pWidth)
{
	mWindowWidth = pWidth;
}

glm::vec3 Player::getPosition() const
{
	return mPosition;
}

GLfloat Player::getHeight() const
{
	return mHeight;
}

const char * Player::getName() const
{
	return mName;
}

int Player::getWindowHeight() const
{
	return mWindowHeight;
}

int Player::getWindowWidht() const
{
	return mWindowWidth;
}

glm::mat4 Player::getViewMatrix() const
{
	return mEye->GetViewMatrix();
}

glm::mat4 Player::getProjectionMatrix(int pHeight, int pWidth) const
{
	return mEye->GetProjectionMatrix(pHeight, pWidth);
}

void Player::ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime)
{
	mEye->ProcessKeyboard(pDirection, deltaTime);
}

void Player::ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset)
{
	mEye->ProcessMouseMovement(pXOffset, pYOffset);
}

void Player::ProcessMouseScroll(GLfloat pYOffset)
{
	mEye->ProcessMouseScroll(pYOffset);
}
