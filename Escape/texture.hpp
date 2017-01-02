#pragma once

// Inclusion of every important external library

// OpenGLExtensionWrangler
#include <glew.h>
// Standard Input/Output
#include <iostream>
// SOImageLoader
#include <SOIL.h>

enum MagnificationMode {
	TEXTURE_FILTER_MAG_NEAREST,
	TEXTURE_FILTER_MAG_BILINEAR,
};

enum MinificationMode {
	TEXTURE_FILTER_MIN_NEAREST,
	TEXTURE_FILTER_MIN_BILINEAR,
	TEXTURE_FILTER_MIN_NEAREST_MIPMAP,
	TEXTURE_FILTER_MIN_BILINEAR_MIPMAP,
	TEXTURE_FILTER_MIN_TRILINEAR
};

// Declaration of the Texture class
class Texture {
// All public member of the class
public:

	// Default Constructor
	Texture(const char* pTextureName, const char* pFilePath);
	// Load the Texture into the Texture Object
	bool loadTexture2D(bool pGenerateMipMaps = false);
	// Binds the Texture to a given Object
	void bind(int pTextureUnit = 0);
	// Sets the filtering of the texture
	void setFiltering(int pMagnification, int pMinification);
	// Returns the current Magnification value
	int getMagnification() const;
	// Returns the current Minification value
	int getMinification() const;
	// Unbinds the texture
	void unbind();

// All private member of the class
private:
	// Name of the texture
	const char* mTextureName;
	// Texture Height
	int mTextureHeight;
	// Texture Width
	int mTextureWidth;
	// Texture ID
	GLuint mTextureID;
	// Sampler ID
	GLuint mSamplerID;
	// Bool to check if mip map was generated
	bool mMipMapCreated;
	// Minification value
	int mMinification;
	// Magnification value
	int	mMagnification;
	// File Path of the texture
	const char* mFilePath;
	

};
