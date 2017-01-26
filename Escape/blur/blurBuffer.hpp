#pragma once

// GLEW Library
#include <glew.h>
// Input/Output Stream
#include <iostream>
// blur shader
#include "./shader/blurShader.hpp"

class BlurFrameBuffers
{
public:
	BlurFrameBuffers(BlurShader * pShader, GLuint pWidth, GLuint pHeight);
	~BlurFrameBuffers();

	void setHorizontal(bool pHorizontal);
	bool getHorizontal() const;
	// call to bind the correct framebuffer and set shader uniforms
	void prepare();
	// return the id of the last used texture to blur it and invert mHorizontal
	GLuint getLastBluredTexture();
	void unbind();
	// starts shader and sets mHorizontal to true
	void startShader();
	void stopShader();

private:
	void init(GLuint pWidth, GLuint pHeight);

private:
	// fbos for horizontal and vertical blur
	GLuint mFBO[2];
	// color buffers for the fbos
	GLuint mColorbuffers[2];
	// used for switching between horizontal and vertical blur
	bool mHorizontal;
	// blur shader
	BlurShader* mShader;
};

