#pragma once

// GLEW
#define GLEW_STATIC
// OpenGLExtensionWrangler
#include <glew.h>
// Standard Input/Output Stream
#include <iostream>
// Matrix 4 x 4
#include <mat4x4.hpp>
// Matrix pointer
#include <gtc/type_ptr.hpp>
// List
#include <list>
// Model class
#include "../../model/model.hpp"
// Entity class
#include "../../entity/entity.hpp"
// Entity shader
#include "../../entity/shader/entityshader.hpp"

// Defines several possible options for render mopdes
enum RenderMode {
	POINTS,
	LINES,
	LINE_STRIP,
	LINE_LOOP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
};


// Declaration of the Entity Renderer
class EntityRenderer
{
public:
	// Constructor
	EntityRenderer(EntityShader* pShader, glm::mat4 pProjectionMatrix);

	//Destructor 
	~EntityRenderer();

	// Render methods:

	// List of Entities
	void render(std::list<Entity> pEntities);
	// List of Entities with given RenderMode
	void render(std::list<Entity> pEntities, RenderMode pMode);
	// Single Entity
	void render(Entity &pEntity);
	// Single Entity with given RenderMode
	void render(Entity &pEntity, RenderMode pMode);

	// Prepare methods:

	// Prepare single Entity (given as direct object)
	void prepareEntity(Entity pEntity);
	// Prepare single Entity (given as pointer to object)
	void prepareEntity(Entity* pEntity);

	// Clean Up Methods:

	// Unbinding the entity
	void unbindEntity();

	// Loader Functions:

	// Load Model Matrix with given Entity (given as object)
	void loadModelMatrix(Entity pEntity);
	// Load Model Matrix with given Entity (given as pointer to object)
	void loadModelMatrix(Entity* pEntity);
	// Load View Matrix
	void loadViewMatrix(glm::mat4 pViewMatrix);
	// Load lights
	void loadLights(std::vector<Light*> pLights);
	// Load clipping plane
	void loadClipPlane(glm::vec4 pClipPlane);
	// Load fog data with given density and gradient
	void loadFogData(GLfloat pDensity, GLfloat pGradient);
	// Load backgroundcolor (R,G,B)
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);

	// Shader functions:

	// Starting the shader
	void startShader();
	// Stopping the shader
	void stopShader();

// All private member of the class
private:
	// Pointer to EntityShader
	EntityShader* mShader;
};
