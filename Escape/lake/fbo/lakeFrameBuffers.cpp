// Inclusion of Declaration
#include "lakeFrameBuffers.hpp"

// Definition of global constants
const int LakeFrameBuffers::REFLECTION_WIDTH = 1280; //320
const int LakeFrameBuffers::REFLECTION_HEIGHT = 720; //180

const int LakeFrameBuffers::REFRACTION_WIDTH = 1280;
const int LakeFrameBuffers::REFRACTION_HEIGHT = 720;

// Constructor
LakeFrameBuffers::LakeFrameBuffers(GLuint pWindowWidth, GLuint pWindowHeight)
{
	// Setting Window Width
	mWindowWidth = pWindowWidth;
	// Setting Window Height
	mWindowHeight = pWindowHeight;
	// Initialize Reflection Buffer
	initReflectionBuffer();
	// Initialize Refraction Buffer
	initRefractionBuffer();

	// Log Message
	std::clog << "The Lake Frame Buffer was created successfully!" << std::endl;
}

// Destructor
LakeFrameBuffers::~LakeFrameBuffers()
{
	
	// Cleaning up all the mess
	this->cleanUp();
	// Log Message
	std::clog << "The Lake Frame Buffer was destroyed successfully!" << std::endl;
}

// Binding Reflection Frame Buffer
void LakeFrameBuffers::bindReflectionFrameBuffer()
{
	this->bindFrameBuffer(mReflectionFrameBuffer, LakeFrameBuffers::REFLECTION_WIDTH, LakeFrameBuffers::REFLECTION_HEIGHT);
}

// Binding Refraction Frame Buffer
void LakeFrameBuffers::bindRefractionFrameBuffer()
{
	this->bindFrameBuffer(mRefractionFrameBuffer, LakeFrameBuffers::REFRACTION_WIDTH, LakeFrameBuffers::REFRACTION_HEIGHT);
}

// Unbind Current Frame Buffer
void LakeFrameBuffers::unbindCurrentFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, mWindowWidth, mWindowHeight);
}

// Returns Reflaction Texture
GLuint LakeFrameBuffers::getReflactionTexture()
{
	return mReflectionTexture;
}

// Returns Refraction Texture
GLuint LakeFrameBuffers::getRefractionTexture()
{
	return mRefractionTexture;
}

// Returns Refraction Depth Texture
GLuint LakeFrameBuffers::getRefractionDepthTexture()
{
	return mRefractionDepthTexture;
}

// Clean up function
void LakeFrameBuffers::cleanUp()
{
	// Delete Refelction Frame Buffer
	glDeleteFramebuffers(1, &mReflectionFrameBuffer);
	glDeleteTextures(1, &mReflectionTexture);
	glDeleteRenderbuffers(1, &mReflectionDepthBuffer);
	// Delete Refraction Frame Buffer
	glDeleteFramebuffers(1, &mRefractionFrameBuffer);
	glDeleteTextures(1, &mRefractionTexture);
	glDeleteTextures(1, &mRefractionDepthTexture);
}

// Initialize Refelction Buffer
void LakeFrameBuffers::initReflectionBuffer()
{
	mReflectionFrameBuffer = this->createFrameBuffer();
	mReflectionTexture = this->createTextureAttachment(LakeFrameBuffers::REFLECTION_WIDTH, LakeFrameBuffers::REFLECTION_HEIGHT);
	mReflectionDepthBuffer = this->createDepthBufferAttachment(LakeFrameBuffers::REFLECTION_WIDTH, LakeFrameBuffers::REFLECTION_HEIGHT);
	this->unbindCurrentFrameBuffer();
}

// Initialize Refraction Buffer
void LakeFrameBuffers::initRefractionBuffer()
{
	mRefractionFrameBuffer = this->createFrameBuffer();
	mRefractionTexture = this->createTextureAttachment(LakeFrameBuffers::REFRACTION_WIDTH, LakeFrameBuffers::REFRACTION_HEIGHT);
	mRefractionDepthTexture = this->createDepthTextureAttachment(LakeFrameBuffers::REFRACTION_WIDTH, LakeFrameBuffers::REFRACTION_HEIGHT);
	this->unbindCurrentFrameBuffer();
}

// Bind Frame Buffer
void LakeFrameBuffers::bindFrameBuffer(GLuint pBuffer, GLuint pWidth, GLuint pHeight)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, pBuffer);
	glViewport(0, 0, pWidth, pHeight);
}

// Returns the new Frame Buffer
GLuint LakeFrameBuffers::createFrameBuffer()
{
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return fbo;
}

// Returns the Texture Attachment
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

// Returns the Depth Texture Attachment
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

// Returns the Depth Buffer Attachment
GLuint LakeFrameBuffers::createDepthBufferAttachment(GLuint pWidth, GLuint pHeight)
{
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pWidth, pHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	return depthBuffer;
}
