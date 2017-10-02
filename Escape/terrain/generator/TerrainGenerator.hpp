#pragma once
#include <iostream>
#include <vector>

#include "../../math/math.hpp"
#include "../../gui/renderer/GuiRenderer.hpp"

#include <glm.hpp>
#include <gtc\noise.hpp>

#include <fstream>
#include <limits>

class TerrainGenerator
{
public:
	// Constructor
	TerrainGenerator(GLuint pMapWidth, GLuint pMapHeight, float pScale, GLuint pNumberOfOctaves, float pPersistance, float pLacunarity);
	// Generates a vector of height values
	std::vector<float> generateHeights();

	// Getters
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
	// Returns the number of octaves
	GLuint getNumberOfOctaves() const;
	// Returns the persistance factor
	float getPersistance() const;
	// Returns the lucunarity factor
	float getLacunarity() const;

	// Setters
	// Sets the current map width to a given value
	void setMapWidth(GLuint pMapWidth);
	// Sets the current map height to a given value
	void setMapHeight(GLuint pMapHeight);
	// Sets the current noise scale factor to a given value
	void setNoiseScale(float pNoiseScale);
	// Sets the number of octaves to a given value
	void setNumberOfOctaves(GLuint pNumberOfOctaves);
	// Sets the npersistance factor to a given value 
	void setPersistance(float pPersistance);
	//Sets the lucunarity factor to a given value
	void setLacunarity(float pLacunarity);

	// Destructor
	~TerrainGenerator();

private:
	// Map Width
	GLuint mMapWidth;
	// Map Height
	GLuint mMapHeight;
	// Noise Scale Factor
	float mNoiseScale;
	// Number of octaves
	GLuint mNumberOfOctaves;
	// Persistance Factor
	float mPersistance;
	// Lacunarity Factor
	float mLacunarity;
	// Height values of the terrain
	std::vector<float> mHeightValues;
};

