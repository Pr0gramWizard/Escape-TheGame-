#pragma once
// Standard Input/Output Stream
#include <iostream>
// Vector class
#include <vector>
// 3x1 Vector GLM
#include <vec3.hpp>
// OpenGLMath
#include <glm.hpp>
// Own Math Library
#include "../../math/math.hpp"
// OpenGLExtensionWrangler
#include <glew.h>
// Loader class
#include "../../loader/loader.hpp"
// Enitity class
#include "../../model/model.hpp"
// Particle Shader
#include "../shader/particleshader.hpp"

// Represents a single particle and its state
struct Particle {
	glm::vec3 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

// Particle Renderer
class ParticleGenerator
{
public:
	ParticleGenerator(ParticleShader* pShader);
	void render(glm::mat4 pViewMatrix);
	void cleanUp();
	~ParticleGenerator();

	void update(GLfloat pDelta, glm::vec3 pObjectPos, GLuint newParticles);

// Private member
private:
	// State
	std::vector<Particle> particles;
	GLuint amount;
	// Render state
	GLuint texture;
	GLuint VAO;
	// Initializes buffer and vertex attributes
	void init();
	// Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
	GLuint firstUnusedParticle();
	// Respawns particle
	void respawnParticle(Particle &particle, glm::vec3 pObjectPos);
	// Particle Shader
	ParticleShader* mShader;

// Private functions
	void updateModelMatrix(glm::vec3 pPosition, GLfloat pScale);
};

