#include "light.hpp"

Light::Light(glm::vec3 pPosition, glm::vec3 pColor)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(glm::vec3(1, 0, 0));
	this->setDiscoColor(pColor);
	this->setDiscoAttenuation(glm::vec3(1, 0, 0));
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setDiscoColor(pColor);
	this->setDiscoAttenuation(pAttenuation);
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setDiscoColor(pDiscoColor);
	this->setDiscoAttenuation(pAttenuation);
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor, glm::vec3 pDiscoAttenuation)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setDiscoColor(pDiscoColor);
	this->setDiscoAttenuation(pDiscoAttenuation);
}

Light::~Light()
{
}

void Light::setPosition(glm::vec3 pPosition)
{
	this->mPosition = pPosition;
}

void Light::setColor(glm::vec3 pColor)
{
	this->mColor = pColor;
}

void Light::setAttenuation(glm::vec3 pAttenuation)
{
	this->mAttenuation = pAttenuation;

	// Prevent dividing by 0
	if (pAttenuation.x == 0) {
		mAttenuation.x = 0.001f;
	}
}

void Light::setDiscoColor(glm::vec3 pColor)
{
	this->mDiscoColor = pColor;
}

void Light::setDiscoAttenuation(glm::vec3 pAttenuation)
{
	this->mDiscoAttenuation = pAttenuation;

	// Prevent dividing by 0
	if (pAttenuation.x == 0) {
		this->mDiscoAttenuation.x = 0.001f;
	}
}

glm::vec3 Light::getPosition() const
{
	return this->mPosition;
}

glm::vec3 Light::getColor() const
{
	return this->mColor;
}

glm::vec3 Light::getAttenuation() const
{
	return this->mAttenuation;
}

void Light::incDiscoTime(float pDelta)
{
	this->mDiscoTime += pDelta;
}

glm::vec3 Light::getDiscoColor() const
{
	// used for formula sin(x)^2 + cos(x)^2 = 1 to interpolate between the vectors
	float partNormal = sin(this->mDiscoTime);
	float partDisco = cos(this->mDiscoTime);

	return (partNormal * partNormal * this->mColor + partDisco * partDisco * this->mDiscoColor);
}

glm::vec3 Light::getDiscoAttenuation() const
{
	// used for formula sin(x)^2 + cos(x)^2 = 1 to interpolate between the vectors
	float partNormal = sin(this->mDiscoTime);
	float partDisco = cos(this->mDiscoTime);

	return (partNormal * partNormal * this->mAttenuation + partDisco * partDisco * this->mDiscoAttenuation);
}

void Light::incPosition(float pX, float pY, float pZ)
{
	this->mPosition.x += pX;
	this->mPosition.y += pY;
	this->mPosition.z += pZ;
}

void Light::invertColor()
{
	this->setColor(glm::vec3(1 - this->mColor.x, 1 - this->mColor.y, 1 - this->mColor.z));
}
