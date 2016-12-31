#pragma once

#include <glew.h>
#include <iostream>
#include <SOIL.h>
using namespace std;

class Texture {
public:
	Texture(GLenum pTextureTarget, const char* pFileName);
	
	bool loadTexture();

	void bindTexture(GLenum pTextureUnit);

private:
	const char* mFileName;
	int mImageWidth;
	int mImageHeight;
	GLenum mTextureTarget;
	GLuint mTextureObject;
	

};
