#pragma once
#include <iostream>
#include <vector>
#include <glm.hpp>

struct Particle
{
	Particle()
		: mPosition(0)
		, mVelocity(0)
		, mColor(0)
		, mfRotate(0)
		, mfAge(0)
		, mfLifeTime(0)
	{}

	glm::vec3   mPosition; // Center point of particle
	glm::vec3   mVelocity; // Current particle velocity
	glm::vec4   mColor;    // Particle color
	float       mfRotate;  // Rotate the particle the center
	float       mfSize;    // Size of the particle
	float       mfAge;
	float       mfLifeTime;
};

typedef std::vector<Particle> ParticleBuffer;