#include "blurBuffer.hpp"

BlurFrameBuffers::BlurFrameBuffers(BlurShader * pShader, GLuint pWidth, GLuint pHeight)
{
	this->mShader = pShader;
	this->setHorizontal(true);
	this->init(pWidth, pHeight);
}


BlurFrameBuffers::~BlurFrameBuffers()
{
}

void BlurFrameBuffers::setHorizontal(bool pHorizontal)
{
	this->mHorizontal = pHorizontal;
}

bool BlurFrameBuffers::getHorizontal() const
{
	return this->mHorizontal;
}

void BlurFrameBuffers::startShader()
{
	this->mShader->use();
}

void BlurFrameBuffers::stopShader()
{
	this->mShader->unuse();
}

void BlurFrameBuffers::init(GLuint pWidth, GLuint pHeight)
{
	// init fbos and colorbuffers
	glGenFramebuffers(2, mFBO);
	glGenTextures(2, mColorbuffers);
	for (GLuint i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO[i]);
		glBindTexture(GL_TEXTURE_2D, mColorbuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, pWidth, pHeight, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // We clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorbuffers[i], 0);
		// Also check if framebuffers are complete (no need for depth buffer)
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}
}
