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
// Particle class
#include "../particle.hpp"
// Particle Shader
#include "../shader/particleshader.hpp"

// Particle Renderer
class ParticleRenderer
{
public:
	ParticleRenderer(Loader pLoader, ParticleShader* pShader);
	void render(std::list<Particle> pParticles, glm::mat4 pViewMatrix);
	void cleanUp();
	void prepare();
	void finishRendering();
	void prepareModel();
	~ParticleRenderer();

// Private member
private:
	// Vertices of the quad that we want to render
	std::vector<GLfloat> mVertices;
	// Indices of the quad
	std::vector<GLint> mIndices;
	// Model of the quad
	Model mQuad;
	// Particle Shader
	ParticleShader* mShader;
	// ViewMatrix
	glm::mat4 mViewMatrix;

// Private functions
	void updateViewMatrix(glm::vec3 pPosition, glm::vec3 pRotation, GLfloat pScale);
};

