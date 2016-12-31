#pragma once

#include <vec3.hpp>

class Light {

public:
	Light(glm::vec3 pPosition, glm::vec3 pColor);
	Light(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation);
	~Light();

	// Setters
	void setPosition(glm::vec3 pPosition);
	void setColor(glm::vec3 pColor);
	void setAttenuation(glm::vec3 pAttenuation);

	// Getters
	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;
	glm::vec3 getAttenuation() const;

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
};