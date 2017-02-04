#pragma once

#include "../shader/lavashader.hpp"
// matrix class
#include <mat4x4.hpp>
// List
#include <list>
// Lava class
#include "../lava.hpp"
// model class
#include "../../model/model.hpp"
// maths
#include "../../math/math.hpp"
// light class
#include "../../light/light.hpp"
// Loader class
#include "../../loader/loader.hpp"

using namespace std;

class LavaRenderer
{
public:
	const static char* LavaRenderer::DUDV_MAP;
	const static char* LavaRenderer::NORMAL_MAP;
	const static float LavaRenderer::LAVA_WAVE_MOVEMENT_SPEED;

public:
	// constructor
	LavaRenderer(LavaShader* pShader, glm::mat4 pProjectionMatrix);
	// destructor
	~LavaRenderer();

	void loadDuDvMap(const char* pFile);
	void loadNormalMap(const char* pFile);

	// render methods
	void render(GLfloat pDeltaTime, glm::mat4 pViewMatrix, Lava &pTerrain, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, bool pDiscoTime);

	// methods that get called before the acutal rendering
	void prepareLava(Lava pLava);
	void prepareLava(Lava* pLava);

	// unbinding all terrains
	void unbindLava();

	// load model matrix for a terrain into the shader
	void loadModelMatrix(Lava pLava);
	void loadModelMatrix(Lava* pLava);
	void loadViewMatrix(glm::mat4 pViewMatrix);
	void loadLights(vector<Light*> pLights, bool pDiscoTime);
	void loadFogData(GLfloat pDensity, GLfloat pGradient);
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);
	void loadNearFar(GLfloat pNear, GLfloat pFar);

	void loadLavaMoveFactor(GLfloat pFactor);


	// use or unuse the shader
	void startShader();
	void stopShader();


private:
	LavaShader* mShader;
	GLuint mDuDvMap;
	GLfloat mLavaMoveFactor;
	GLuint mNormalMap;
};

