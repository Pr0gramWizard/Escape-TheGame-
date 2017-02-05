#pragma once
// OpenGLExtensionWrangler
#include <glew.h>
// Standard Input/Output Stream
#include <iostream>

// Declaration of the Lake Frame Buffer class
class ShadowFrameBuffers
{
	// All public functions of the class
public:
	// Constructor
	ShadowFrameBuffers(GLuint pWindowWidth, GLuint pWindowHeight);
	// Destructor
	~ShadowFrameBuffers();

	// Binding Buffer
	// Reflection Buffer
	void bindShadowFrameBuffer();
	// Unbinding Buffer
	void unbindShadowFrameBuffer();

	// Getter for Textures
	// Depth cubemap
	GLuint getDepthCubemap();

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
};