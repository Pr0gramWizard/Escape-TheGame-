#pragma once
// OpenGLExtensionWrangler
#include <glew.h>
// Standard Input/Output Stream
#include <iostream>
// OpenGLMath 
#include <glm.hpp>
// Matrix Transformation
#include <gtc/matrix_transform.hpp>
// vectors
#include <vector>

// Declaration of the Lake Frame Buffer class
class ShadowFrameBuffer
{
	// All public functions of the class
public:
	// Constructor
	ShadowFrameBuffer(GLuint pWindowWidth, GLuint pWindowHeight);
	// Destructor
	~ShadowFrameBuffer();

	// Binding Buffer
	// Reflection Buffer
	void bindShadowFrameBuffer();
	// Unbinding Buffer
	void unbindShadowFrameBuffer();

	// Getter for Textures
	// Depth cubemap
	GLuint getDepthCubemap();

	std::vector<glm::mat4> getShadowTransforms(glm::vec3 pLightPos) const;

	// Clean Up function
	void cleanUp();

	// All public member of the class
public:
	static const int SHADOW_WIDTH;
	static const int SHADOW_HEIGHT;

	// All private functions of the class
private:
	// Initialise Functions
	void init();

	// Binding the frame buffer
	void bindFrameBuffer(GLuint pBuffer, GLuint pWidth, GLuint pHeight);

	// All private member of the class
private:
	GLuint mDepthCubeMap;
	GLuint mDepthMapFBO;
	// Window Width
	GLuint mWindowWidth;
	// Window Height
	GLuint mWindowHeight;

	glm::mat4 mShadowProjection;
};