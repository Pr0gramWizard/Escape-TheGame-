#pragma once

// GLEW
#include <glew.h>
#include <iostream>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>
#include <list>
// model class
#include "../object.hpp"
#include "../shader/objectshader.hpp"

using namespace std;

class ObjectRenderer
{
public:
	// constructor
	ObjectRenderer(ObjectShader* pShader, glm::mat4 pProjectionMatrix);

	// render methods
	void render();

	// Add to List
	void addToList(Object* pObject);

	// Clean List
	void cleanUp();

	// load model matrix for a terrain into the shader
	void loadModelMatrix(Object* pObject);
	void loadViewMatrix(glm::mat4 pViewMatrix);
	void loadFogData(GLfloat pDensity, GLfloat pGradient);
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);

	// use or unuse the shader
	void startShader();
	void stopShader();

private:
	std::list<Object*> mObjects;
	ObjectShader* mShader;
};
