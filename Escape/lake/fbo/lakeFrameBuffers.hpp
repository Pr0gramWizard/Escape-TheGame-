#pragma once
// OpenGLExtensionWrangler
#include <glew.h>
// Standard Input/Output Stream
#include <iostream>

// Declaration of the Lake Frame Buffer class
class LakeFrameBuffers
{
// All public functions of the class
public:
	// Constructor
	LakeFrameBuffers(GLuint pWindowWidth, GLuint pWindowHeight);
	// Destructor
	~LakeFrameBuffers();

	// Binding Buffer
	// Reflection Buffer
	void bindReflectionFrameBuffer();
	// Refraction Buffer
	void bindRefractionFrameBuffer();
	// Unbinding Buffer
	void unbindCurrentFrameBuffer();

	// Getter for Textures
	// Reflaction Texture
	GLuint getReflactionTexture();
	// Refraction Texture
	GLuint getRefractionTexture();
	// RefractionDepth Texture
	GLuint getRefractionDepthTexture();

	// Clean Up function
	void cleanUp();

// All public member of the class
public:
	// Reflection Width
	static const int REFLECTION_WIDTH;
	// Reflection Height
	static const int REFLECTION_HEIGHT;
	// Reflection Width
	static const int REFRACTION_WIDTH;
	// Reflection Height
	static const int REFRACTION_HEIGHT;

// All private functions of the class
private:
	// Initialise Functions
	void initReflectionBuffer();
	void initRefractionBuffer();

	// Binding the frame buffer
	void bindFrameBuffer(GLuint pBuffer, GLuint pWidth, GLuint pHeight);

	// Create Functions
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(GLuint pWidth, GLuint pHeight);
	GLuint createDepthTextureAttachment(GLuint pWidth, GLuint pHeight);
	GLuint createDepthBufferAttachment(GLuint pWidth, GLuint pHeight);

// All private member of the class
private:
	// Reflection FrameBuffer
	GLuint mReflectionFrameBuffer;
	// Reflection Texture
	GLuint mReflectionTexture;
	// Reflection DepthBuffer
	GLuint mReflectionDepthBuffer;
	// Refraction FrameBuffer
	GLuint mRefractionFrameBuffer;
	// Refraction Texture
	GLuint mRefractionTexture;
	// Refraction DepthTexture
	GLuint mRefractionDepthTexture;
	// Window Width
	GLuint mWindowWidth;
	// Window Height
	GLuint mWindowHeight;
};