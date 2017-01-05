#pragma once

#include "../shader/lakeshader.hpp"
// matrix class
#include <mat4x4.hpp>
// List
#include <list>
// lake class
#include "../lake.hpp"
// lake fbo class
#include "../fbo/lakeFrameBuffers.hpp"
// model class
#include "../../model/model.hpp"
// maths
#include "../../math/math.hpp"
// light class
#include "../../light/light.hpp"

using namespace std;

class LakeRenderer
{
public:
	// constructor
	LakeRenderer(LakeShader* pShader, glm::mat4 pProjectionMatrix, LakeFrameBuffers* pLakeFbos);
	// destructor
	~LakeRenderer();

	// render methods
	void render(glm::mat4 pViewMatrix, Lake &pTerrain);

	// methods that get called before the acutal rendering
	void prepare();
	void prepareLake(Lake pLake);
	void prepareLake(Lake* pLake);

	// unbinding all terrains
	void unbindLake();

	// load model matrix for a terrain into the shader
	void loadModelMatrix(Lake pLake);
	void loadModelMatrix(Lake* pLake);
	void loadViewMatrix(glm::mat4 pViewMatrix);
	void loadLights(vector<Light*> pLights);

	// use or unuse the shader
	void startShader();
	void stopShader();


private:
	LakeShader* mShader;
	LakeFrameBuffers* mLakeFbos;
};

