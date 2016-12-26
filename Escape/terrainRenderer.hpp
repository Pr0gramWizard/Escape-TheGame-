#pragma once

#include "testshader.hpp"
#include <mat4x4.hpp>
// List
#include <list>
// terrain class
#include "terrain.hpp"
// model class
#include "model.hpp"
// maths
#include "math.hpp"

using namespace std;

class TerrainRenderer
{
public:
	TerrainRenderer(Testshader* pShader, glm::mat4 pProjectionMatrix);
	~TerrainRenderer();

	void render(list<Terrain> pTerrains);
	void render(Terrain pTerrain);

	void prepareTerrain(Terrain pTerrain);
	void unbindTerrain();
	void loadModelMatrix(Terrain pTerrain);


private:
	Testshader* mShader;
};

