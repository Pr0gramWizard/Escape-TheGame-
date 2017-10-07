#include "TerrainGenerator.hpp"



TerrainGenerator::TerrainGenerator(GLuint pMapWidth, GLuint pMapHeight, float pScale, GLuint pNumberOfOctaves, float pPersistance, float pLacunarity){
	this->setMapWidth(pMapWidth);
	this->setMapHeight(pMapHeight);
	this->setNoiseScale(pScale);
	this->setNumberOfOctaves(pNumberOfOctaves);
	this->setPersistance(pPersistance);
	this->setLacunarity(pLacunarity);

	mHeightValues = this->generateHeights();
	std::cout << "Terrain Generator was started successfully!" << std::endl;
}

std::vector<float> TerrainGenerator::generateHeights() {
	std::vector<float> noiseMap;
	noiseMap.reserve(this->getMapWidth() * this->getMapWidth());

	if (this->getNosieScale() <= 0) {
		this->setNoiseScale(0.0001f);
	}

	float maxNoiseHeight = -std::numeric_limits<float>::max();
	float minNoiseHeight = std::numeric_limits<float>::max();

	for (unsigned int y = 0; y < this->getMapWidth(); ++y) {
		for (unsigned int x = 0; x < this->getMapWidth(); ++x) {
			float amplitude = 1;
			float frequency = 1;
			float noiseHeight = 0;

			for (unsigned int i = 0; i < this->getNumberOfOctaves(); ++i) {
				float sampleX = (x / this->getNosieScale()) * frequency;
				float sampleY = (y / this->getNosieScale()) * frequency;

				float perlinValue = Math::getNoise(sampleX, sampleY);

				noiseHeight += perlinValue * amplitude;
				amplitude *= this->getPersistance();
				frequency *= this->getLacunarity();
			}

			if (noiseHeight > maxNoiseHeight) {
				maxNoiseHeight = noiseHeight;
			} else if (noiseHeight < minNoiseHeight) {
				minNoiseHeight = noiseHeight;
			}

			noiseMap.push_back(noiseHeight);
		}
	}
	/*
	for (unsigned int k = 0; k < noiseMap.size(); ++k) {
		noiseMap[k] = Math::inverseLerp(minNoiseHeight, maxNoiseHeight, noiseMap[k]);
	}
	*/

	return noiseMap;
}

std::vector<float> TerrainGenerator::getRGBValues() const{
	std::vector<float> temp = { 0 };
	return temp;
}

GLuint TerrainGenerator::getNumberOfOctaves() const
{
	return mNumberOfOctaves;
}

float TerrainGenerator::getPersistance() const
{
	return mPersistance;
}

float TerrainGenerator::getLacunarity() const
{
	return mLacunarity;
}

GLuint TerrainGenerator::getMapWidth() const
{
	return mMapWidth;
}

GLuint TerrainGenerator::getMapHeight() const
{
	return mMapHeight;
}

float TerrainGenerator::getNosieScale() const
{
	return mNoiseScale;
}

std::vector<float> TerrainGenerator::getHeightValues() const
{
	return mHeightValues;
}

void TerrainGenerator::setMapWidth(GLuint pMapWidth){
	mMapWidth = pMapWidth;
}

void TerrainGenerator::setMapHeight(GLuint pMapHeight){
	mMapHeight = pMapHeight;
}

void TerrainGenerator::setNoiseScale(float pNoiseScale){
	mNoiseScale = pNoiseScale;
}

void TerrainGenerator::setNumberOfOctaves(GLuint pNumberOfOctaves){
	mNumberOfOctaves = pNumberOfOctaves;
}

void TerrainGenerator::setPersistance(float pPersistance){
	mPersistance = pPersistance;
}

void TerrainGenerator::setLacunarity(float pLacunarity){
	mLacunarity = pLacunarity;
}


TerrainGenerator::~TerrainGenerator(){
	std::cout << "Terrain Generator was stopped successfully!" << std::endl;
}
