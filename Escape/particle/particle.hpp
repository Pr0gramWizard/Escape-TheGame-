#include <iostream>
#include <vector>
#include <glew.h>
#include <glm.hpp>
#include <vec3.hpp>
#include "../player/player.hpp"

#include "shader/particleShader.hpp"


class Particle
{
// Public functions
public:
	// Default Constructor
	Particle(glm::vec3 pPosition, glm::vec3 pVelocity, GLfloat pGravityEffect, GLfloat pLifeSpan, GLfloat pRotation, GLfloat pScale);
	// Update Function
	bool update(GLfloat deltaTime);

	// Getters
	glm::vec3 getPosition() const;
	glm::vec3 getVelocity() const;
	GLfloat getGravityEffect() const;
	GLfloat getLifeSpan() const;
	GLfloat getRotation() const;
	GLfloat getScale() const;

	// Setters
	void setPosition(glm::vec3 pPosition);
	void setVelocity(glm::vec3 pVelocity);
	void setGravityEffect(GLfloat pGravityEffect);
	void setLifeSpan(GLfloat pLifeSpan);
	void setRotation(GLfloat pRotation);
	void setScale(GLfloat pScale);

// Private member
private:
	// Particle position
	glm::vec3 mPosition;
	// Particle Velocity
	glm::vec3 mVelocity;
	// Effect of Gravity on the Particle
	GLfloat mGravityEffect;
	// Life Span of the particle
	GLfloat mLifeSpan;
	// Rotation of the particle
	GLfloat mRotation;
	// Scale of each particle
	GLfloat mScale;
	// Elapsed Time
	GLfloat mElapsedTime;
	// Pointer to the Player class
	Player* mPlayer;


};
