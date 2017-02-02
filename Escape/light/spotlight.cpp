#include "spotlight.hpp"

SpotLight::SpotLight(glm::vec3 pPosition, glm::vec3 pColor)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(glm::vec3(1, 0, 0));
	this->setTarget(glm::vec3(0));
	this->setFactor(1);
}

SpotLight::SpotLight(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pTarget, float pFactor)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(glm::vec3(1, 0, 0));
	this->setTarget(pTarget);
	this->setFactor(pFactor);
}

SpotLight::SpotLight(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pTarget, float pFactor, glm::vec3 pAttenuation)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setTarget(pTarget);
	this->setFactor(pFactor);
}

SpotLight::SpotLight(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
}

SpotLight::~SpotLight()
{
}

void SpotLight::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

void SpotLight::setColor(glm::vec3 pColor)
{
	mColor = pColor;
}

void SpotLight::setAttenuation(glm::vec3 pAttenuation)
{
	mAttenuation = pAttenuation;

	// Prevent dividing by 0
	if (pAttenuation.x == 0) {
		mAttenuation.x = 0.001f;
	}
}

void SpotLight::setTarget(glm::vec3 pTarget)
{
	this->mTarget = pTarget;
}

void SpotLight::setFactor(float pFactor)
{
	this->mFactor = pFactor;
}

glm::vec3 SpotLight::getPosition() const
{
	return mPosition;
}

glm::vec3 SpotLight::getColor() const
{
	return mColor;
}

glm::vec3 SpotLight::getAttenuation() const
{
	return mAttenuation;
}

glm::vec3 SpotLight::getTarget() const
{
	return this->mTarget;
}

float SpotLight::getFactor() const
{
	return this->mFactor;
}

void SpotLight::incPosition(float pX, float pY, float pZ)
{
	mPosition.x += pX;
	mPosition.y += pY;
	mPosition.z += pZ;
}

void SpotLight::invertColor()
{
	this->setColor(glm::vec3(1 - mColor.x, 1 - mColor.y, 1 - mColor.z));
}
