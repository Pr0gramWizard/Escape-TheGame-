#include "light.hpp"

Light::Light(glm::vec3 pPosition, glm::vec3 pColor)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(glm::vec3(1, 0, 0));
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
}

Light::~Light()
{
}

void Light::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

void Light::setColor(glm::vec3 pColor)
{
	mColor = pColor;
}

void Light::setAttenuation(glm::vec3 pAttenuation)
{
	mAttenuation = pAttenuation;

	// Prevent dividing by 0
	if (pAttenuation.x == 0) {
		mAttenuation.x = 1;
	}
}

glm::vec3 Light::getPosition() const
{
	return mPosition;
}

glm::vec3 Light::getColor() const
{
	return mColor;
}

glm::vec3 Light::getAttenuation() const
{
	return mAttenuation;
}

void Light::incPosition(float pX, float pY, float pZ)
{
	mPosition.x += pX;
	mPosition.y += pY;
	mPosition.z += pZ;
}

void Light::invertColor()
{
	this->setColor(glm::vec3(1 - mColor.x, 1 - mColor.y, 1 - mColor.z));
}
