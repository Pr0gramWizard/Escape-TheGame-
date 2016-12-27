#pragma once

// GLEW
#define GLEW_STATIC
#include <glew.h>
#include <iostream>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>
// model class
#include "model.hpp"
#include "entity.hpp"
#include "shader.hpp"
#include "testshader.hpp"

enum RenderMode {
	POINTS,
	LINES,
	LINE_STRIP,
	LINE_LOOP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
};

class EntityRenderer
{
public:
	// constructor
	EntityRenderer();
	// destructor
	~EntityRenderer();

	// method that should get called before rendering
	void prepare();

	// adds a shader to the renderer
	void addShader(const char* pVertexShader, const char* pFragmentShader);

	// adds a matrix uniform attribute
	void addUniformAttribute(glm::mat4 pMatrix, const char* pAttributeName);

	// enables the shader
	void enableShader();

	// disables the shader
	void disableShader();

	// renders an entity with the given RenderMode
	void render(Entity pEntity, Testshader *pShader, RenderMode pMode);

	// renders an entity with RenderMode = GL_LINES
	void render(Entity pModel, Testshader *pShader);

private:
	Shader* mShader;
};

