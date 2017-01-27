#pragma once

// GLEW Library
#include <glew.h>
// Input/Output Stream
#include <iostream>
// blur shader
//#include "./shader/blurShader.hpp"

class PreBloomFBO
{
public:
	PreBloomFBO(GLuint pWidth, GLuint pHeight);
	~PreBloomFBO();

	void unbind();
	void bind();
	// index has to be 0 or 1
	GLuint getColorBuffer(GLboolean pIndex);

private:
	void init(GLuint pWidth, GLuint pHeight);

private:
	// fbos for blooming scene
	GLuint mFBO;
	/**
	 *	color buffers for the fbos
	 *  0 -> scene
	 *  1 -> only parts to bloom
	 */
	GLuint mColorbuffers[2];
};

