#include "particlesystem.hpp"

// Default Constructor
ParticleSystem::ParticleSystem()
{
	// Not intialized
	mInitialized = false;
	// Set read buffer to 0
	mCurrentReadBuffer = 0;

	std::cout << "Started the Particle Shader" << std::endl;
}

ParticleSystem::~ParticleSystem()
{
	std::cout << "Stopped the Particle Shader" << std::endl;
}

bool ParticleSystem::initParticleSystem()
{
	// If the Program was already initialized we stop
	if (mInitialized)
	{
		return false;
	}

	// Set up array
	const char* sVaryings[NUM_PARTICLE_ATTRIBUTES] =
	{
		"vPositionOut",
		"vVelocityOut",
		"vColorOut",
		"fLifeTimeOut",
		"fSizeOut",
		"iTypeOut",
	};

	shVertexUpdate.LoadShader("./shaders/particle/particles_update.vert", GL_VERTEX_SHADER);
	shGeomUpdate.LoadShader("./shaders/particle/particles_update.geom", GL_GEOMETRY_SHADER);
	shFragUpdate.LoadShader("./shaders/particle/particles_update.frag", GL_FRAGMENT_SHADER);


	spUpdateParticles.CreateProgram();
	spUpdateParticles.AddShaderToProgram(&shVertexUpdate);
	spUpdateParticles.AddShaderToProgram(&shGeomUpdate);
	for (int i = 0; i < NUM_PARTICLE_ATTRIBUTES; ++i)
	{
		(spUpdateParticles.GetProgramID(), 6, sVaryings, GL_INTERLEAVED_ATTRIBS);
	}
		spUpdateParticles.LinkProgram();


	// Rendering program

	shVertexRender.LoadShader("./shaders/particle/particles_render.vert", GL_VERTEX_SHADER);
	shGeomRender.LoadShader("./shaders/particle/particles_render.geom", GL_GEOMETRY_SHADER);
	shFragRender.LoadShader("./shaders/particle/particles_render.frag", GL_FRAGMENT_SHADER);

	spRenderParticles.CreateProgram();

	spRenderParticles.AddShaderToProgram(&shVertexRender);
	spRenderParticles.AddShaderToProgram(&shGeomRender);
	spRenderParticles.AddShaderToProgram(&shFragRender);

	spRenderParticles.LinkProgram();


	glGenTransformFeedbacks(1, &mTransformBuffer);
	glGenQueries(1, &mQuery);

	glGenBuffers(2, mParticleBuffer);
	glGenVertexArrays(2, mVAO);

	CParticle partInitialization;
	partInitialization.mType = PARTICLE_TYPE_GENERATOR;

	for(int i = 0; i < 2; ++i)
	{
		glBindVertexArray(mVAO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, mParticleBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CParticle)*MAX_PARTICLES_ON_SCENE, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(CParticle), &partInitialization);

		for (int j = 0; j < NUM_PARTICLE_ATTRIBUTES; ++j)
		{
			glEnableVertexAttribArray(j);
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)12); // Velocity
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)24); // Color
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)36); // Lifetime
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)40); // Size
		glVertexAttribPointer(5, 1, GL_INT, GL_FALSE, sizeof(CParticle), (const GLvoid*)44); // Type
	}

	// Set read buffer to 0
	mCurrentReadBuffer = 0;
	// We have a particle
	mNumberOfParticles = 1;
	// Set status to true
	mInitialized = true;

	// Return status
	return true;
}

float grandf(float fMin, float fAdd)
{
	float fRandom = float(rand() % (RAND_MAX + 1)) / float(RAND_MAX);
	return fMin + fAdd*fRandom;
}

void ParticleSystem::renderParticles()
{
	if (!mInitialized)return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(0);

	glDisable(GL_RASTERIZER_DISCARD);

	spRenderParticles.UseProgram();
	spRenderParticles.SetUniform("matrices.mProj", &mProjectionMatrix);
	spRenderParticles.SetUniform("matrices.mView", &mViewMatrix);
	spRenderParticles.SetUniform("vQuad1", &mQuad1);
	spRenderParticles.SetUniform("vQuad2", &mQuad2);
	spRenderParticles.SetUniform("gSampler", 0);

	glBindVertexArray(mVAO[mCurrentReadBuffer]);
	glDisableVertexAttribArray(1); // Disable velocity, because we don't need it for rendering

	glDrawArrays(GL_POINTS, 0, mNumberOfParticles);

	glDepthMask(1);
	glDisable(GL_BLEND);
}

void ParticleSystem::updateParticles(float pDelta)
{
	if (!mInitialized)return;

	spUpdateParticles.UseProgram();

	glm::vec3 vUpload;
	spUpdateParticles.SetUniform("fTimePassed", pDelta);
	spUpdateParticles.SetUniform("vGenPosition", mPosition);
	spUpdateParticles.SetUniform("vGenVelocityMin", mMinVelocity);
	spUpdateParticles.SetUniform("vGenVelocityRange", mVelocityRange);
	spUpdateParticles.SetUniform("vGenColor", mColor);
	spUpdateParticles.SetUniform("vGenGravityVector", mGravity);

	spUpdateParticles.SetUniform("fGenLifeMin", mMinLifeTime);
	spUpdateParticles.SetUniform("fGenLifeRange", mLifeTimeRange);

	spUpdateParticles.SetUniform("fGenSize", mSize);
	spUpdateParticles.SetUniform("iNumToGenerate", 0);


	mElapsedTime += pDelta;

	if (mElapsedTime > mNextSpawnTime)
	{
		spUpdateParticles.SetUniform("generateNumber", mNumberToGenerate);
		mElapsedTime -= mNextSpawnTime;

		glm::vec3 vRandomSeed = glm::vec3(grandf(-10.0f, 20.0f), grandf(-10.0f, 20.0f), grandf(-10.0f, 20.0f));
		spUpdateParticles.SetUniform("vRandomSeed", &vRandomSeed);
	}

	glEnable(GL_RASTERIZER_DISCARD);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, mTransformBuffer);

	glBindVertexArray(mVAO[mCurrentReadBuffer]);
	glEnableVertexAttribArray(1); // Re-enable velocity

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mParticleBuffer[1 - mCurrentReadBuffer]);

	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, mQuery);
	glBeginTransformFeedback(GL_POINTS);

	glDrawArrays(GL_POINTS, 0, mNumberOfParticles);

	glEndTransformFeedback();

	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	glGetQueryObjectiv(mQuery, GL_QUERY_RESULT, &mNumberOfParticles);

	mCurrentReadBuffer = 1 - mCurrentReadBuffer;

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

void ParticleSystem::setGeneratorProperties(glm::vec3 pPosition, glm::vec3 pMinVelocity, glm::vec3 pMaxVelocity, glm::vec3 pGravity, glm::vec3 pColor, float pMinLifeTime, float pMaxLifeTime, float pSize, float pEvery, int pNumberOfParticles)
{
	mPosition = pPosition;
	mMinVelocity = pMinVelocity;
	mVelocityRange = pMaxVelocity - pMinVelocity;

	mGravity = pGravity;
	mColor = pColor;
	mSize = pSize;

	mMinLifeTime = pMinLifeTime;
	mLifeTimeRange = pMaxLifeTime - pMinLifeTime;

	mNextSpawnTime = pEvery;
	mElapsedTime = 0.8f;

	mNumberToGenerate = pNumberOfParticles;
}

void ParticleSystem::clearAllParticles()
{
}

bool ParticleSystem::releaseParticleSystem()
{
	return false;
}

int ParticleSystem::getNumberOfParticles() const
{
	return mNumberOfParticles;
}

void ParticleSystem::setMatrix(glm::mat4 pProjectionMatrix, glm::vec3 pEye, glm::vec3 pView, glm::vec3 pUpVector)
{
	mProjectionMatrix = pProjectionMatrix;

	mViewMatrix = glm::lookAt(pEye, pView, pUpVector);
	pView = pView - pEye;
	pView = glm::normalize(pView);
	mQuad1 = glm::cross(pView, pUpVector);
	mQuad1 = glm::normalize(mQuad1);
	mQuad2 = glm::cross(pView, mQuad1);
	mQuad2 = glm::normalize(mQuad2);
}
