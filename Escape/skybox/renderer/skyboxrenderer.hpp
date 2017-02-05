#pragma once

// GLEW
#include <glew.h>
#include <iostream>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>

#include "../skybox.hpp"
#include "../shader/skyboxshader.hpp"


class SkyboxRenderer
{
public:
	// constructor
	SkyboxRenderer(SkyboxShader* pShader, glm::mat4 pProjectionMatrix);
	// destructor
	~SkyboxRenderer();

	// render methods
	void render(Skybox* pSkybox);

	// methods that get called before the acutal rendering
	void prepareSkybox(Skybox* pEntity);

	// unbinding all terrains
	void unbindSkybox();

	// load model matrix for a terrain into the shader
	void loadViewMatrix(glm::mat4 pViewMatrix);
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);

	// use or unuse the shader
	void startShader();
	void stopShader();

private:
	SkyboxShader* mShader;
};
