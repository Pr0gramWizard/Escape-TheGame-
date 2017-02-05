// Inclusion of Declaration
#include "shadowfbo.hpp"

// Definition of global constants
const int ShadowFrameBuffers::SHADOW_WIDTH = 1024;
const int ShadowFrameBuffers::SHADOW_HEIGHT = 1024;

// Constructor
ShadowFrameBuffers::ShadowFrameBuffers(GLuint pWindowWidth, GLuint pWindowHeight)
{
	// Setting Window Width
	mWindowWidth = pWindowWidth;
	// Setting Window Height
	mWindowHeight = pWindowHeight;
	// Initialize Reflection Buffer
	init();

	// Log Message
	std::clog << "The Shadow Frame Buffer was created successfully!" << std::endl;
}

// Destructor
ShadowFrameBuffers::~ShadowFrameBuffers()
{

	// Cleaning up all the mess
	this->cleanUp();
	// Log Message
	std::clog << "The Shadow Frame Buffer was destroyed successfully!" << std::endl;
}

// Unbind Current Frame Buffer
void ShadowFrameBuffers::unbindShadowFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, mWindowWidth, mWindowHeight);
}


// Returns Depth Texture
GLuint ShadowFrameBuffers::getDepthCubemap()
{
	return mDepthCubeMap;
}

// Clean up function
void ShadowFrameBuffers::cleanUp()
{
	// Delete Refelction Frame Buffer
	glDeleteFramebuffers(1, &mDepthMapFBO);
	glDeleteTextures(1, &mDepthCubeMap);
}

void ShadowFrameBuffers::init()
{
}

// Bind Frame Buffer
void ShadowFrameBuffers::bindFrameBuffer(GLuint pBuffer, GLuint pWidth, GLuint pHeight)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, pBuffer);
	glViewport(0, 0, pWidth, pHeight);
}

void ShadowFrameBuffers::bindShadowFrameBuffer()
{
	this->bindFrameBuffer(mDepthMapFBO, ShadowFrameBuffers::SHADOW_WIDTH, ShadowFrameBuffers::SHADOW_HEIGHT);
}
