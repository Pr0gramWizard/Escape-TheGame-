#pragma once

// GLEW
#define GLEW_STATIC
#include <glew.h>
#include <iostream>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>
#include <list>
// model class
#include "../../model/model.hpp"
#include "../../entity/entity.hpp"
#include "../../entity/shader/entityshader.hpp"

enum RenderMode {
	POINTS2,
	LINES,
	LINE_STRIP,
	LINE_LOOP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
};

using namespace std;

class EntityRenderer
{
public:
	// constructor
	EntityRenderer(EntityShader* pShader, glm::mat4 pProjectionMatrix);
	// destructor
	~EntityRenderer();

	// render methods
	void render(list<Entity> pEntities);
	void render(list<Entity> pEntities, RenderMode pMode);
	void render(Entity &pEntity);

	// methods that get called before the acutal rendering
	void prepareEntity(Entity pEntity);
	void prepareEntity(Entity* pEntity);

	// unbinding all terrains
	void unbindEntity();

	// load model matrix for a terrain into the shader
	void loadModelMatrix(Entity pEntity);
	void loadModelMatrix(Entity* pEntity);
	void loadViewMatrix(glm::mat4 pViewMatrix);
	void loadLights(vector<Light*> pLights);
	void loadClipPlane(glm::vec4 pClipPlane);
	void loadFogData(GLfloat pDensity, GLfloat pGradient);
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);

	// use or unuse the shader
	void startShader();
	void stopShader();

private:
	EntityShader* mShader;
};
