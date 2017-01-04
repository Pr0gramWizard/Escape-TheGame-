#include "texture.hpp"

Texture2D::Texture2D(const char* pTextureName, const char* pFilePath)
{
	mFilePath = pFilePath;
	mTextureName = pTextureName;
	std::cout << mTextureName << " Texture was created successfully!" << std::endl;
	std::cout << "It is located at: " << mFilePath << std::endl;
}

bool Texture2D::loadTexture2D(bool pGenerateMipMaps)
{
	// Loading the image with SOIL
	unsigned char* image = SOIL_load_image(mFilePath, &mTextureWidth, &mTextureHeight, 0, SOIL_LOAD_RGB);

	// If the file could not be found
	if (image == 0)
	{
		// Return an error message
		std::cout << "There was an error opening the given texture file!" << std::endl;
		// Stop loading process
		return 1;
	}

	// Create new Texture Object
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// Create RGB Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mTextureWidth, mTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// Generate Mipmap only if user implies so
	if (pGenerateMipMaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	// Free the image data by SOIL
	SOIL_free_image_data(image);
	// Create new Sampler Object
	glGenSamplers(1, &mSamplerID);
	// Set the status of mip map
	mMipMapCreated = pGenerateMipMaps;
	// Success
	return 0;
}

void Texture2D::bind(int pTextureUnit)
{
	glActiveTexture(GL_TEXTURE0 + pTextureUnit);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glBindSampler(pTextureUnit, mSamplerID);
}

void Texture2D::setFiltering(int pMagnification, int pMinification)
{
	// Set magnification filter
	if (pMagnification == TEXTURE_FILTER_MAG_NEAREST)
		glSamplerParameteri(mSamplerID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	else if (pMagnification == TEXTURE_FILTER_MAG_BILINEAR)
		glSamplerParameteri(mSamplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set minification filter
	if (pMinification == TEXTURE_FILTER_MIN_NEAREST)
		glSamplerParameteri(mSamplerID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	else if (pMinification == TEXTURE_FILTER_MIN_BILINEAR)
		glSamplerParameteri(mSamplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	else if (pMinification == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
		glSamplerParameteri(mSamplerID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	else if (pMinification == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
		glSamplerParameteri(mSamplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	else if (pMinification == TEXTURE_FILTER_MIN_TRILINEAR)
		glSamplerParameteri(mSamplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	mMinification = pMinification;
	mMagnification = pMagnification;
}

int Texture2D::getMagnification() const
{
	return mMagnification;
}

int Texture2D::getMinification() const
{
	return mMinification;
}

void Texture2D::unbind()
{
	glDeleteSamplers(1, &mSamplerID);
	glDeleteTextures(1, &mTextureID);

}
