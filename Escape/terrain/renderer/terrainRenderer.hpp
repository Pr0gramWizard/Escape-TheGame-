#pragma once


// matrix class
#include <mat4x4.hpp>
// List
#include <list>
// terrain class
#include "../terrain.hpp"
// model class
#include "../../model/model.hpp"
// maths
#include "../../math/math.hpp"
// light class
#include "../../light/light.hpp"
// Terrain shader
#include "../shader/terrainshader.hpp"

using namespace std;

class TerrainRenderer
{
public:
	// constructor
	TerrainRenderer(TerrainShader* pShader, glm::mat4 pProjectionMatrix);
	// destructor
	~TerrainRenderer();

	// render methods
	void render(list<Terrain> pTerrains);
	void render(Terrain &pTerrain);

	// methods that get called before the acutal rendering
	void prepare();
	void prepareTerrain(Terrain pTerrain);
	void prepareTerrain(Terrain* pTerrain);

	// unbinding all terrains
	void unbindTerrain();

	// load model matrix for a terrain into the shader
	void loadModelMatrix(Terrain pTerrain);
	void loadModelMatrix(Terrain* pTerrain);
	void loadViewMatrix(glm::mat4 pViewMatrix);
	void loadLights(vector<Light*> pLights);
	void loadClipPlane(glm::vec4 pClipPlane);

	// use or unuse the shader
	void startShader();
	void stopShader();


private:
	TerrainShader* mShader;
};
