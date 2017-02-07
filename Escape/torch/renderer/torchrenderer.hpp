#pragma once

// GLEW
#include <glew.h>
#include <iostream>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>
#include <list>
// model class
#include "../Torch.hpp"
#include "../shader/Torchshader.hpp"

using namespace std;

class TorchRenderer
{
public:
	// constructor
	TorchRenderer(TorchShader* pShader, glm::mat4 pProjectionMatrix);

	// render methods
	void render(Torch &Torch);
	void render(Torch* Torch);

	// load model matrix for a terrain into the shader
	void loadModelMatrix(Torch* pTorch);
	void loadViewMatrix(glm::mat4 pViewMatrix);
	void loadFogData(GLfloat pDensity, GLfloat pGradient);
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);
	void loadClipPlane(glm::vec4 pClipPlane);
	void loadLights(vector<Light*> pLights, bool pDiscoTime);

	// use or unuse the shader
	void startShader();
	void stopShader();

private:
	TorchShader* mShader;
};
