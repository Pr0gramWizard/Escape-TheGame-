#include "particle.hpp"

Particle::Particle(glm::vec3 pPosition, glm::vec3 pVelocity, GLfloat pGravityEffect, GLfloat pLifeSpan, GLfloat pRotation, GLfloat pScale)
{
	this->setPosition(pPosition);
	this->setVelocity(pVelocity);
	this->setGravityEffect(pGravityEffect);
	this->setLifeSpan(pLifeSpan);
	this->setRotation(pRotation);
	this->setScale(pScale);
}

bool Particle::update(GLfloat deltaTime)
{
	this->mVelocity.y = mPlayer->GRAVITY * this->getGravityEffect() * deltaTime;
	
	glm::vec3 change = change * deltaTime;

	this->setPosition(this->getPosition() + change);

	mElapsedTime += deltaTime;

	return mElapsedTime < this->getLifeSpan();

}

glm::vec3 Particle::getPosition() const
{
	return mPosition;
}

glm::vec3 Particle::getVelocity() const
{
	return mVelocity;
}

GLfloat Particle::getGravityEffect() const
{
	return mGravityEffect;
}

GLfloat Particle::getLifeSpan() const
{
	return mLifeSpan;
}

glm::vec3 Particle::getRotation() const
{
	return glm::vec3(mRotation, mRotation, mRotation);
}

GLfloat Particle::getScale() const
{
	return mScale;
}

void Particle::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

void Particle::setVelocity(glm::vec3 pVelocity)
{
	mVelocity = pVelocity;
}

void Particle::setGravityEffect(GLfloat pGravityEffect)
{
	mGravityEffect = pGravityEffect;
}

void Particle::setLifeSpan(GLfloat pLifeSpan)
{
	mLifeSpan = pLifeSpan;
}

void Particle::setRotation(GLfloat pRotation)
{
	mRotation = pRotation;
}

void Particle::setScale(GLfloat pScale)
{
	mScale = pScale;
}
