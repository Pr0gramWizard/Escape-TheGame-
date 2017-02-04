#include "particlegenerator.hpp"


ParticleGenerator::ParticleGenerator(ParticleShader* pShader, glm::mat4 pProjectionMatrix, GLuint pAmount)
{
	this->init();
	this->amount = pAmount;
	this->particles = std::vector<Particle>(pAmount);
	//this->texture = 0;
	mShader = pShader;
	mShader->use();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	mShader->unuse();
}

void ParticleGenerator::render(glm::mat4 pViewMatrix)
{
	glDepthMask(false);
	// Use additive blending to give it a 'glow' effect
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	mShader->use();
	mShader->loadViewMatrix(pViewMatrix);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	for (Particle particle : this->particles)
	{
		if (particle.Life > 0.0f)
		{
			// update modelmatrix and load it to the shader
			updateModelMatrix(particle.Position, 0.05f);
			//this->shader.SetVector4f("color", particle.Color);
			//this->texture.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
	// Don't forget to reset to default blending mode
	glBindVertexArray(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	glDepthMask(true);
}

void ParticleGenerator::cleanUp()
{

}

void ParticleGenerator::updateModelMatrix(glm::vec3 pPosition, GLfloat pScale)
{
	glm::mat4 ModelMatrix = Math::getTransformationMatrix(pPosition, 0.0f, 0.0f, 0.0f, pScale);

	mShader->loadModelMatrix(ModelMatrix);
}

ParticleGenerator::~ParticleGenerator()
{

}

void ParticleGenerator::init()
{
	// Set up mesh and attribute properties
	GLuint VBO;
	/*GLfloat particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};*/

	GLfloat particle_quad[] = {
		-0.5f, 0.5f, 
		-0.5f, -0.5f,
		0.5f, 0.5f
	};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	// Create this->amount default particle instances
	for (GLuint i = 0; i < this->amount; ++i)
		this->particles.push_back(Particle());
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
GLuint ParticleGenerator::firstUnusedParticle()
{
	// First search from last used particle, this will usually return almost instantly
	for (GLuint i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (GLuint i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, glm::vec3 pObjectPos)
{
	//GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
	particle.Position = pObjectPos;
	particle.Color = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	particle.Life = 1.0f;
	particle.Velocity = glm::vec3(0.0f, 1.0f, 0.0f);
}

void ParticleGenerator::update(GLfloat pDelta, glm::vec3 pObjectPos, GLuint newParticles)
{
	// Add new particles 
	for (GLuint i = 0; i < newParticles; ++i)
	{
		int unusedParticle = this->firstUnusedParticle();
		this->respawnParticle(this->particles[unusedParticle], pObjectPos);
	}
	// Update all particles
	for (GLuint i = 0; i < this->amount; ++i)
	{
		Particle &p = this->particles[i];
		p.Life -= pDelta; // reduce life
		if (p.Life > 0.0f)
		{	// particle is alive, thus update
			// std::cout << p.Life << std::endl;
			p.Velocity.y += -10*pDelta;
			p.Position += p.Velocity;
			p.Color.a -= pDelta * 2.5;
		}
	}
}