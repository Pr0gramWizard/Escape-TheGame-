#pragma once

#include <vec3.hpp>
#include <math.h>
#include <glm.hpp>

#include <iostream>

class Light {

public:
	Light(glm::vec3 pPosition, glm::vec3 pColor);
	Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation);
	Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor);
	Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor, float pDiscoOffset);
	Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor, glm::vec3 pDiscoAttenuation);
	Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation, glm::vec3 pDiscoColor, glm::vec3 pDiscoAttenuation, float pDiscoOffset);
	~Light();

	// Setters
	void setPosition(glm::vec3 pPosition);
	void setColor(glm::vec3 pColor);
	void setAttenuation(glm::vec3 pAttenuation);
	void setDiscoColor(glm::vec3 pColor);
	void setDiscoAttenuation(glm::vec3 pAttenuation);

	// Getters
	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;
	glm::vec3 getAttenuation() const;

	void incDiscoTime(float pDelta);

	// return interpolated vectors
	glm::vec3 getDiscoColor() const;
	glm::vec3 getDiscoAttenuation() const;

	// Increases position by an offset
	void incPosition(float pX, float pY, float pZ);

	// Inverts the light's color
	void invertColor();

private:
	// Position in world space
	glm::vec3 mPosition;
	// Color
	glm::vec3 mColor;
	// Limits the light's spread
	glm::vec3 mAttenuation;
	// Disco color
	glm::vec3 mDiscoColor;
	// Limits the light's spread
	glm::vec3 mDiscoAttenuation;
	// Disco time
	float mDiscoTime;
};