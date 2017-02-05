// Inclusion of Declaration
#include "shadowfbo.hpp"

// Definition of global constants
const int ShadowFrameBuffer::SHADOW_WIDTH = 1024;
const int ShadowFrameBuffer::SHADOW_HEIGHT = 1024;

// Constructor
ShadowFrameBuffer::ShadowFrameBuffer(GLuint pWindowWidth, GLuint pWindowHeight)
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
ShadowFrameBuffer::~ShadowFrameBuffer()
{

	// Cleaning up all the mess
	this->cleanUp();
	// Log Message
	std::clog << "The Shadow Frame Buffer was destroyed successfully!" << std::endl;
}

// Unbind Current Frame Buffer
void ShadowFrameBuffer::unbindShadowFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, mWindowWidth, mWindowHeight);
}


// Returns Depth Texture
GLuint ShadowFrameBuffer::getDepthCubemap()
{
	return mDepthCubeMap;
}

// Returns view matrices for given lightsource
std::vector<glm::mat4> ShadowFrameBuffer::getShadowTransforms(glm::vec3 pLightPos) const
{
	std::vector<glm::mat4> shadowTransforms;

	shadowTransforms.push_back(mShadowProjection *
		glm::lookAt(pLightPos, pLightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	shadowTransforms.push_back(mShadowProjection *
		glm::lookAt(pLightPos, pLightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	shadowTransforms.push_back(mShadowProjection *
		glm::lookAt(pLightPos, pLightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	shadowTransforms.push_back(mShadowProjection *
		glm::lookAt(pLightPos, pLightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	shadowTransforms.push_back(mShadowProjection *
		glm::lookAt(pLightPos, pLightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	shadowTransforms.push_back(mShadowProjection *
		glm::lookAt(pLightPos, pLightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	return shadowTransforms;
}

// Clean up function
void ShadowFrameBuffer::cleanUp()
{
	// Delete Refelction Frame Buffer
	glDeleteFramebuffers(1, &mDepthMapFBO);
	glDeleteTextures(1, &mDepthCubeMap);
}

void ShadowFrameBuffer::init()
{
	// set shadow projection
	GLfloat aspect = (GLfloat)ShadowFrameBuffer::SHADOW_WIDTH / (GLfloat)ShadowFrameBuffer::SHADOW_HEIGHT;
	GLfloat near = 1.0f;
	GLfloat far = 25.0f;
	mShadowProjection = glm::perspective(glm::radians(90.0f), aspect, near, far);

	// create framebuffer
	glGenFramebuffers(1, &mDepthMapFBO);

	// create cubemap
	glGenTextures(1, &mDepthCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mDepthCubeMap);
	for (GLuint i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, ShadowFrameBuffer::SHADOW_WIDTH, ShadowFrameBuffer::SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Attach cubemap as depth map FBO's color buffer
	glBindFramebuffer(GL_FRAMEBUFFER, mDepthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mDepthCubeMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Bind Frame Buffer
void ShadowFrameBuffer::bindFrameBuffer(GLuint pBuffer, GLuint pWidth, GLuint pHeight)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, pBuffer);
	glViewport(0, 0, pWidth, pHeight);
}

void ShadowFrameBuffer::bindShadowFrameBuffer()
{
	this->bindFrameBuffer(mDepthMapFBO, ShadowFrameBuffer::SHADOW_WIDTH, ShadowFrameBuffer::SHADOW_HEIGHT);
}
