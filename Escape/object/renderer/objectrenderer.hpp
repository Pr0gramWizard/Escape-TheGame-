#pragma once

// GLEW
#define GLEW_STATIC
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
	ObjectRenderer(EntityShader* pShader, glm::mat4 pProjectionMatrix);
	// destructor
	~ObjectRenderer();

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
	void loadLight(Light *pLight);
	void loadClipPlane(glm::vec4 pClipPlane);

	// use or unuse the shader
	void startShader();
	void stopShader();

private:
	ObjectShader* mShader;
};
