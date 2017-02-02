#pragma once

#include <vec3.hpp>

class SpotLight {

public:
	SpotLight(glm::vec3 pPosition, glm::vec3 pColor);
	SpotLight(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pTarget, float pFactor);
	SpotLight(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pTarget, float pFactor, glm::vec3 pAttenuation);
	SpotLight(glm::vec3 pPosition, glm::vec3 pColor, glm::vec3 pAttenuation);
	~SpotLight();

	// Setters
	void setPosition(glm::vec3 pPosition);
	void setColor(glm::vec3 pColor);
	void setAttenuation(glm::vec3 pAttenuation);
	void setTarget(glm::vec3 pTarget);
	void setFactor(float pFactor);

	// Getters
	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;
	glm::vec3 getAttenuation() const;
	glm::vec3 getTarget() const;;
	float getFactor() const;

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
	// Target
	glm::vec3 mTarget;
	// Spotlight Factor
	float mFactor;
};