#pragma once
// Standard Input/Output library
#include <iostream>
// String 
#include <string>
// Simple OpenGL Image Loading
#include <SOIL.h>
#include <vector>
#include <glew.h>
#include <glfw3.h>
#include <gl\GL.h>

// Declaration of the Skybox Texture class
class SkyboxTexture{

public:
	// Default constructor with file path
	SkyboxTexture(std::string pFilePath);
	// Loading the cubemap in a texture ID
	void loadTexture();
	// Returns File Path
	std::string getFilePath() const;
	// Returns texture ID
	GLuint getTextureID() const;
	// Default destructor
	~SkyboxTexture();

private:
	// Texture ID
	GLuint mTextureID;
	// File Path
	std::string mFilePath;
	// Skybox directions
	std::vector<std::string> mDirections = { "right","left","top","bottom","back","front" };
};

