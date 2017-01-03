#include "lakeFrameBuffers.hpp"

const int LakeFrameBuffers::REFLECTION_WIDTH = 320;
const int LakeFrameBuffers::REFLECTION_HEIGHT = 180;

const int LakeFrameBuffers::REFRACTION_WIDTH = 1280;
const int LakeFrameBuffers::REFRACTION_HEIGHT = 720;

LakeFrameBuffers::LakeFrameBuffers()
{
}


LakeFrameBuffers::~LakeFrameBuffers()
{
}

void LakeFrameBuffers::bindReflectionFrameBuffer()
{
}

void LakeFrameBuffers::bindRefractionFrameBuffer()
{
}

void LakeFrameBuffers::unbindCurrentFrameBuffer()
{
}

GLuint LakeFrameBuffers::getReflactionTexture()
{
	return GLuint();
}

GLuint LakeFrameBuffers::getRefractionTexture()
{
	return GLuint();
}

GLuint LakeFrameBuffers::getRefractionDepthTexture()
{
	return GLuint();
}

void LakeFrameBuffers::cleanUp()
{
}

void LakeFrameBuffers::initReflectionBuffer()
{
}

void LakeFrameBuffers::initRefractionBuffer()
{
}

void LakeFrameBuffers::bindFrameBuffer(GLuint pBuffer, GLuint pWidth, GLuint pHeight)
{
}

GLuint LakeFrameBuffers::createFrameBuffer()
{
	return GLuint();
}

GLuint LakeFrameBuffers::createTextureAttachment(GLuint pWidth, GLuint pHeight)
{
	return GLuint();
}

GLuint LakeFrameBuffers::createDepthTextureAttachment(GLuint pWidth, GLuint pHeight)
{
	return GLuint();
}
