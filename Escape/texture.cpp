#include "texture.hpp"

Texture::Texture(GLenum TextureTarget, const char* FileName)
{
	mTextureTarget = TextureTarget;
	mFileName = FileName;
}


bool Texture::loadTexture()
{

	// Loading the image with SOIL
	unsigned char* image = SOIL_load_image(mFileName, &mImageWidth, &mImageHeight, 0, SOIL_LOAD_RGB);

	if (image == NULL)
	{
		std::cout << "There was a problem loading the image: " << mFileName << " !" << std::endl;
		return 1;
	}

	glGenTextures(1, &mTextureObject);
	glBindTexture(mTextureTarget, mTextureObject);
	glTexImage2D(mTextureTarget, 0, GL_RGBA,mImageWidth, mImageHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameterf(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(mTextureTarget, 0);

	return true;
}

void Texture::bindTexture(GLenum pTextureUnit)
{
	glActiveTexture(pTextureUnit);
	glBindTexture(mTextureTarget, mTextureObject);
}
