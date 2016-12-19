#include "player.hpp"

Player::Player(glm::vec3 pPosition, glm::vec3 pVelocity, GLfloat pHeight, const char * pName)
{
	setPositionAbsolute(pPosition);
	setVelocity(pVelocity);
	setHeight(pHeight);
	setName(pName);
}

Player::Player(glm::vec3 pPosition, GLfloat pHeight, const char * pName)
{
	setPositionAbsolute(pPosition);
	setVelocity(glm::vec3(0, 0, 0));
	setHeight(pHeight);
	setName(pName);
}

void Player::move()
{
	//apply gravity
	/* TODO */

	//collision dectection with terrain
	/* TODO */
}

void Player::setPosition(glm::vec3 pOffset)
{
	mPosition.x += pOffset.x;
	mPosition.y += pOffset.y;
	mPosition.z += pOffset.z;
}

void Player::setPositionAbsolute(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

void Player::setVelocity(glm::vec3 pVelocity)
{
	mVelocity = pVelocity;
}

void Player::setHeight(GLfloat pHeight)
{
	mHeight = pHeight;
}

void Player::setName(const char * pName)
{
	mName = pName;
}

glm::vec3 Player::getPosition() const
{
	return mPosition;
}

glm::vec3 Player::getVelocity() const
{
	return mVelocity;
}

GLfloat Player::getHeight() const
{
	return mHeight;
}

const char * Player::getName() const
{
	return mName;
}