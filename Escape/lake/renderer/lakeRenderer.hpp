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
// Loader class
#include "../../loader/loader.hpp"

using namespace std;

class LakeRenderer
{
public:
	const static char* LakeRenderer::DUDV_MAP;
	const static char* LakeRenderer::NORMAL_MAP;
	const static float LakeRenderer::LAKE_WAVE_MOVEMENT_SPEED;

public:
	// constructor
	LakeRenderer(LakeShader* pShader, glm::mat4 pProjectionMatrix, LakeFrameBuffers* pLakeFbos);
	// destructor
	~LakeRenderer();

	void loadDuDvMap(const char* pFile);
	void loadNormalMap(const char* pFile);

	// render methods
	void render(GLfloat pDeltaTime, glm::mat4 pViewMatrix, Lake &pTerrain, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);

	// methods that get called before the acutal rendering
	void prepareLake(Lake pLake);
	void prepareLake(Lake* pLake);

	// unbinding all terrains
	void unbindLake();

	// load model matrix for a terrain into the shader
	void loadModelMatrix(Lake pLake);
	void loadModelMatrix(Lake* pLake);
	void loadViewMatrix(glm::mat4 pViewMatrix);
	void loadLights(vector<Light*> pLights);
	void loadFogData(GLfloat pDensity, GLfloat pGradient);
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);
	void loadNearFar(GLfloat pNear, GLfloat pFar);

	void loadWaterMoveFactor(GLfloat pFactor);

	// use or unuse the shader
	void startShader();
	void stopShader();


private:
	LakeShader* mShader;
	LakeFrameBuffers* mLakeFbos;
	GLuint mDuDvMap;
	GLfloat mLakeMoveFactor;
	GLuint mNormalMap;
};

