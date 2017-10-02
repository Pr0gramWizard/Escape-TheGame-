#include "TerrainGenerator.hpp"



TerrainGenerator::TerrainGenerator(GLuint pMapWidth, GLuint pMapHeight, float pScale){
	this->setMapWidth(pMapWidth);
	this->setMapHeight(pMapHeight);
	this->setNoiseScale(pScale);
	mHeightValues = this->generateHeights();
	std::cout << "Terrain Generator was started successfully!" << std::endl;
}

void TerrainGenerator::render() {
	temp->render();
}

std::vector<float> TerrainGenerator::generateHeights() {
	std::vector<float> noiseMap;
	noiseMap.reserve(this->getMapWidth() * this->getMapWidth());

	if (this->getNosieScale() <= 0) {
		this->setNoiseScale(0.0001f);
	}

	for (unsigned int y = 0; y < this->getMapWidth(); ++y) {
		for (unsigned int x = 0; x < this->getMapWidth(); ++x) {
			float sampleX = x / this->getNosieScale();
			float sampleY = y / this->getNosieScale();

			float perlinValue = Math::getSmoothNoise(sampleX, sampleY);
			noiseMap.push_back(perlinValue);
		}
	}

	return noiseMap;
}

std::vector<float> TerrainGenerator::getRGBValues() const{
	std::ofstream myfile;
	myfile.open("rgbValues.log");
	

	std::vector<float> temp = mHeightValues;
	for (unsigned int i = 0; i < mHeightValues.size(); ++i) {
		temp[i] += 1;
		temp[i] /= 2.0f;
		temp[i] *= 255;
		temp[i] = (int)temp[i];
		myfile << temp[i] << std::endl;
	}
	myfile.close();

	return temp;
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


TerrainGenerator::~TerrainGenerator(){
	std::cout << "Terrain Generator was stopped successfully!" << std::endl;
}
