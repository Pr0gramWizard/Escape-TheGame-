#pragma once

#include <glew.h>

class LakeFrameBuffers
{
public:
	LakeFrameBuffers(GLuint pWindowWidth, GLuint pWindowHeight);
	~LakeFrameBuffers();

	// binding buffers
	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void unbindCurrentFrameBuffer();

	// texture getters
	GLuint getReflactionTexture();
	GLuint getRefractionTexture();
	GLuint getRefractionDepthTexture();

	// clean up
	void cleanUp();

public:
	static const int REFLECTION_WIDTH;
	static const int REFLECTION_HEIGHT;

	static const int REFRACTION_WIDTH;
	static const int REFRACTION_HEIGHT;

private:
	// init functions
	void initReflectionBuffer();
	void initRefractionBuffer();

	// binding a framebuffer
	void bindFrameBuffer(GLuint pBuffer, GLuint pWidth, GLuint pHeight);

	// create functions
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(GLuint pWidth, GLuint pHeight);
	GLuint createDepthTextureAttachment(GLuint pWidth, GLuint pHeight);
	GLuint createDepthBufferAttachment(GLuint pWidth, GLuint pHeight);


private:
	GLuint mReflectionFrameBuffer;
	GLuint mReflectionTexture;
	GLuint mReflectionDepthBuffer;

	GLuint mRefractionFrameBuffer;
	GLuint mRefractionTexture;
	GLuint mRefractionDepthTexture;

	GLuint mWindowWidth;
	GLuint mWindowHeight;
};