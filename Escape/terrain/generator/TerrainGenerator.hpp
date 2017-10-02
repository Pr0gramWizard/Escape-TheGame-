#pragma once
#include <iostream>
#include <vector>

#include "../../math/math.hpp"
#include "../../gui/renderer/GuiRenderer.hpp"

#include <fstream>

class TerrainGenerator
{
public:
	// Constructor
	TerrainGenerator(GLuint pMapWidth, GLuint pMapHeight, float pScale);
	// Generates a vector of height values
	std::vector<float> generateHeights();
	// Returns the current map width
	GLuint getMapWidth() const;
	// Returns the current map height
	GLuint getMapHeight() const;
	// Returns the current noise scale factor
	float getNosieScale() const;
	// Returns the current height value vector
	std::vector<float> getHeightValues() const;
	// Returns the current height value vector
	std::vector<float> getRGBValues() const;
	// Sets the current map width to a given value
	void setMapWidth(GLuint pMapWidth);
	// Sets the current map height to a given value
	void setMapHeight(GLuint pMapHeight);
	// Sets the current noise scale factor to a given value
	void setNoiseScale(float pNoiseScale);
	void render();
	// Destructor
	~TerrainGenerator();

private:
	GLuint mMapWidth;
	GLuint mMapHeight;
	float mNoiseScale;
	std::vector<float> mHeightValues;

	Loader* cLoader;
	GuiShader* mShader;
	GuiRenderer* temp;
	GLuint textureID;
};

