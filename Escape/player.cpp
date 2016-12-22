#include "player.hpp"

const GLfloat Player::MOVESPEED = 10;
const GLfloat Player::TURNSPEED = 180;
const GLfloat Player::GRAVITY = -90;
//needed?
const GLfloat Player::JUMPPOWER = 45;

Player::Player(glm::vec3 pPosition, GLfloat pHeight, const char * pName)
{
	setPosition(pPosition);
	setHeight(pHeight);
	setName(pName);
	mCurrentMoveSpeed = 0;
	mCurrentTurnSpeed = 0;
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