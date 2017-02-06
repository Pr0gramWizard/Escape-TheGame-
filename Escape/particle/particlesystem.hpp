#pragma once
// Standrad Input/Output
#include <iostream>
// OpenGLMath
#include <glm.hpp>
// OpenGLExtensionWrangler
#include <glew.h>
// Extra Matrix Function
#include <gtc\matrix_transform.hpp>
// Shader
#include "pShader.h"

#define NUM_PARTICLE_ATTRIBUTES 6
#define MAX_PARTICLES_ON_SCENE 100000

#define PARTICLE_TYPE_GENERATOR 0
#define PARTICLE_TYPE_NORMAL 1

class CParticle
{
public:
	glm::vec3 mPosition;
	glm::vec3 mVelocity;
	glm::vec3 mColor;
	float mLifeTime;
	float mSize;
	int mType;
};

// Declaration of the particle system class
class ParticleSystem
{
// All public methods of the class
public:

	// Default Constructor
	ParticleSystem();
	// Default Destructor
	~ParticleSystem();
	// Initialize Particle System
	bool initParticleSystem();
	// Render All Particles
	void renderParticles();
	// Update Particles (depending on deltatime)
	void updateParticles(float pDelta);
	// Set Properties of the Particle Generator
	void setGeneratorProperties(glm::vec3 pPosition, glm::vec3 pMinVelocity, glm::vec3 pMaxVelocity, glm::vec3 pGravity, glm::vec3 pColor, float pMinLifeTime, float pMaxLifeTime, float pSize, float pEvery, int pNumberOfParticles);
	// Delete All Particles
	void clearAllParticles();
	// Release Particle System
	bool releaseParticleSystem();
	// Returns Number of Particles
	int getNumberOfParticles() const;
	// Set ViewMatrix
	void setMatrix(glm::mat4 pProjectionMatrix, glm::vec3 pEye, glm::vec3 pView, glm::vec3 pUpVector);

// All private member of the class
private:
	// Status of Particle System
	bool mInitialized;
	// Transform Buffer
	GLuint mTransformBuffer;
	// Particle Buffer
	GLuint mParticleBuffer[2];
	// VertexArrayObject
	GLuint mVAO[2];
	// Query 
	GLuint mQuery;
	// TextureID
	GLuint mTextureID;
	// ReadBuffer
	GLint mCurrentReadBuffer;
	// Number of Particles
	GLint mNumberOfParticles;
	// Projection Matrix
	glm::mat4 mProjectionMatrix;
	// View Matrix
	glm::mat4 mViewMatrix;
	// First and Second Quad
	glm::vec3 mQuad1, mQuad2;
	// Elapsed Time
	float mElapsedTime;
	// Next Spawn Time
	float mNextSpawnTime;
	// Position
	glm::vec3 mPosition;
	// Minimum Velocity
	glm::vec3 mMinVelocity;
	// Velocity Range
	glm::vec3 mVelocityRange;
	// Gravity
	glm::vec3 mGravity;
	// Color
	glm::vec3 mColor;
	// Minimum Lifetime
	float mMinLifeTime;
	// LifeTime Range
	float mLifeTimeRange;
	// Size
	float mSize;
	// Number To Generator
	int mNumberToGenerate;
	// Render Shader
	PShader shVertexRender, shGeomRender, shFragRender;
	PShader shVertexUpdate, shGeomUpdate, shFragUpdate;
	PShaderProgram spRenderParticles;
	PShaderProgram spUpdateParticles;





};

