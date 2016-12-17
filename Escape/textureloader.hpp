#pragma once

#include <glew.h>
#include <iostream>
#include <SOIL.h>
using namespace std;

class TextureLoader {
public:
	// helps us to reduce duplicated code:
	// textureType might be GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D...
	// internalFormat might be GL_RGBA, GL_SRGB_ALPHA, ...
	GLuint loadTexture(const char* filename, GLenum textureType, GLenum internalFormat)
	{
		GLuint textureHandle;
		int width, height;
		unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

		glGenTextures(1, &textureHandle);
		glBindTexture(textureType, textureHandle);

		//change GL_RGB?
		glTexImage2D(textureType, 0, internalFormat, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		//adapt parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(textureType, 0);

		SOIL_free_image_data(image); // Not needed anymore!

		return textureHandle;
	}
};
