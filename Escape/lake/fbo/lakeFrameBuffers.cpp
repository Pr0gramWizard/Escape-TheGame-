#include "lakeFrameBuffers.hpp"

const int LakeFrameBuffers::REFLECTION_WIDTH = 1290; //1280 320
const int LakeFrameBuffers::REFLECTION_HEIGHT = 720; //720 180

const int LakeFrameBuffers::REFRACTION_WIDTH = 1280;
const int LakeFrameBuffers::REFRACTION_HEIGHT = 720;

LakeFrameBuffers::LakeFrameBuffers(GLuint pWindowWidth, GLuint pWindowHeight)
{
	mWindowWidth = pWindowWidth;
	mWindowHeight = pWindowHeight;

	initReflectionBuffer();
	initRefractionBuffer();
}


LakeFrameBuffers::~LakeFrameBuffers()
{
	this->cleanUp();
}

void LakeFrameBuffers::bindReflectionFrameBuffer()
{
	this->bindFrameBuffer(mReflectionFrameBuffer, LakeFrameBuffers::REFLECTION_WIDTH, LakeFrameBuffers::REFLECTION_HEIGHT);
}

void LakeFrameBuffers::bindRefractionFrameBuffer()
{
	this->bindFrameBuffer(mRefractionFrameBuffer, LakeFrameBuffers::REFRACTION_WIDTH, LakeFrameBuffers::REFRACTION_HEIGHT);
}

void LakeFrameBuffers::unbindCurrentFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, mWindowWidth, mWindowHeight);
}

GLuint LakeFrameBuffers::getReflactionTexture()
{
	return mReflectionTexture;
}

GLuint LakeFrameBuffers::getRefractionTexture()
{
	return mRefractionTexture;
}

GLuint LakeFrameBuffers::getRefractionDepthTexture()
{
	return mRefractionDepthTexture;
}

void LakeFrameBuffers::cleanUp()
{
	glDeleteFramebuffers(1, &mReflectionFrameBuffer);
	glDeleteTextures(1, &mReflectionTexture);
	glDeleteRenderbuffers(1, &mReflectionDepthBuffer);

	glDeleteFramebuffers(1, &mRefractionFrameBuffer);
	glDeleteTextures(1, &mRefractionTexture);
	glDeleteTextures(1, &mRefractionDepthTexture);

}

void LakeFrameBuffers::initReflectionBuffer()
{
	mReflectionFrameBuffer = this->createFrameBuffer();
	mReflectionTexture = this->createTextureAttachment(LakeFrameBuffers::REFLECTION_WIDTH, LakeFrameBuffers::REFLECTION_HEIGHT);
	mReflectionDepthBuffer = this->createDepthBufferAttachment(LakeFrameBuffers::REFLECTION_WIDTH, LakeFrameBuffers::REFLECTION_HEIGHT);
	this->unbindCurrentFrameBuffer();
}

void LakeFrameBuffers::initRefractionBuffer()
{
	mRefractionFrameBuffer = this->createFrameBuffer();
	mRefractionTexture = this->createTextureAttachment(LakeFrameBuffers::REFRACTION_WIDTH, LakeFrameBuffers::REFRACTION_HEIGHT);
	mRefractionDepthTexture = this->createDepthTextureAttachment(LakeFrameBuffers::REFRACTION_WIDTH, LakeFrameBuffers::REFRACTION_HEIGHT);
	this->unbindCurrentFrameBuffer();
}

void LakeFrameBuffers::bindFrameBuffer(GLuint pBuffer, GLuint pWidth, GLuint pHeight)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, pBuffer);
	glViewport(0, 0, pWidth, pHeight);
}

GLuint LakeFrameBuffers::createFrameBuffer()
{
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return fbo;
}

GLuint LakeFrameBuffers::createTextureAttachment(GLuint pWidth, GLuint pHeight)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pWidth, pHeight,
		0, GL_RGB, GL_UNSIGNED_BYTE, nullptr); // maybe 0 instead of nullptr
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	return texture;
}

GLuint LakeFrameBuffers::createDepthTextureAttachment(GLuint pWidth, GLuint pHeight)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, pWidth, pHeight,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr); // maybe 0 instead of nullptr
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
	return texture;
}

GLuint LakeFrameBuffers::createDepthBufferAttachment(GLuint pWidth, GLuint pHeight)
{
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pWidth, pHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	return depthBuffer;
}
