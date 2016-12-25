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

class Renderer
{
public:
	Renderer();
	~Renderer();

	void prepare();
	void addShader(const char* pVertexShader, const char* pFragmentShader);
	void addUniformAttribute(glm::mat4 pMatrix, const char* pAttributeName);
	void enableShader();
	void disableShader();
	void render(Entity pEntity, Testshader *pShader, RenderMode pMode);
	void render(Entity pModel, Testshader *pShader);

private:
	Shader* mShader;
};

