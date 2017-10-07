#include "light.hpp"

Light::Light(glm::vec3 pPosition, glm::vec3 pColor)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(glm::vec3(1, 0, 0));
	this->setDiscoColor(pColor);
	this->setDiscoAttenuation(glm::vec3(1, 0, 0));
	this->mDiscoTime = 0.0f;
	this->mDiscoFrequency = 1.0f;
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setDiscoColor(pColor);
	this->setDiscoAttenuation(pAttenuation);
	this->mDiscoTime = 0.0f;
	this->mDiscoFrequency = 1.0f;
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setDiscoColor(pDiscoColor);
	this->setDiscoAttenuation(pAttenuation);
	this->mDiscoTime = 0.0f;
	this->mDiscoFrequency = 1.0f;
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor, float pDiscoOffset, float pDiscoFrequency)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setDiscoColor(pDiscoColor);
	this->setDiscoAttenuation(pAttenuation);
	this->mDiscoTime = pDiscoOffset;
	this->mDiscoFrequency = pDiscoFrequency;
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor, glm::vec3 pDiscoAttenuation)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setDiscoColor(pDiscoColor);
	this->setDiscoAttenuation(pDiscoAttenuation);
	this->mDiscoTime = 0.0f;
	this->mDiscoFrequency = 1.0f;
}

Light::Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor, glm::vec3 pDiscoAttenuation, float pDiscoOffset, float pDiscoFrequency)
{
	this->setPosition(pPosition);
	this->setColor(pColor);
	this->setAttenuation(pAttenuation);
	this->setDiscoColor(pDiscoColor);
	this->setDiscoAttenuation(pDiscoAttenuation);
	this->mDiscoTime = pDiscoOffset;
	this->mDiscoFrequency = pDiscoFrequency;
}

Light::~Light()
{
	glDeleteTextures(1, &mDepthCubemap);
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

void Light::setDepthCubemap(GLuint pDepth)
{
	this->mDepthCubemap = pDepth;
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
	this->mDiscoTime += (float) (this->mDiscoFrequency * M_PI * pDelta);
}

glm::vec3 Light::getDiscoColor() const
{
	// used for formula sin(x)^2 + cos(x)^2 = 1 to interpolate between the vectors
	float partDisco = sin(this->mDiscoTime);
	partDisco *= partDisco;

	glm::vec3 mix = glm::mix(this->mColor, this->mDiscoColor, partDisco);

	return mix;
}

glm::vec3 Light::getDiscoAttenuation() const
{
	// used for formula sin(x)^2 + cos(x)^2 = 1 to interpolate between the vectors
	float partDisco = sin(this->mDiscoTime);
	partDisco *= partDisco;

	glm::vec3 mix = glm::mix(this->mAttenuation, this->mDiscoAttenuation, partDisco);

	return mix;
}

GLuint Light::getDepthCubemap() const
{
	return this->mDepthCubemap;
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
