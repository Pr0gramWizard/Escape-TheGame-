#include "particlerenderer.hpp"


ParticleRenderer::ParticleRenderer(Loader pLoader, ParticleShader* pShader)
{
	mQuad = pLoader.loadDataToVao(mVertices, mIndices);
	mShader = pShader;
}

void ParticleRenderer::render(std::list<Particle> pParticles, glm::mat4 pViewMatrix)
{
	mViewMatrix = pViewMatrix;
	mShader->use();
	mShader->loadViewMatrix(mViewMatrix);
	prepare();

	for (Particle particle : pParticles)
	{
		updateViewMatrix(particle.getPosition(), particle.getRotation(), particle.getScale());
		glDrawArrays(GL_TRIANGLE_STRIP, 0, mQuad.getVerticesCount());
	}
	finishRendering();
}

void ParticleRenderer::cleanUp()
{

}

void ParticleRenderer::updateViewMatrix(glm::vec3 pPosition, glm::vec3 pRotation, GLfloat pScale)
{
	glm::mat4 ModelMatrix = Math::getTransformationMatrix(pPosition, pRotation.x, pRotation.y, pRotation.z, pScale);

	mShader->loadModelMatrix(ModelMatrix);
}

void ParticleRenderer::prepare()
{
	mShader->use();
	glBindVertexArray(mQuad.getVaoId());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);

}

void ParticleRenderer::finishRendering()
{

	glDepthMask(true);
	glDisable(GL_BLEND);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	mShader->unuse();
}

ParticleRenderer::~ParticleRenderer()
{

}

void ParticleRenderer::prepareModel()
{
	mVertices.push_back(-0.5f);
	mVertices.push_back(0.5f);
	mVertices.push_back(-0.5f);
	mVertices.push_back(-0.5f);
	mVertices.push_back(0.5f);
	mVertices.push_back(0.5f);
	mVertices.push_back(0.5f);
	mVertices.push_back(-0.5f);

	mIndices.push_back(0);
	mIndices.push_back(1);
	mIndices.push_back(2);
	mIndices.push_back(1);
	mIndices.push_back(2);
	mIndices.push_back(3);


}
