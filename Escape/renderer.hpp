#pragma once

// GLEW
#define GLEW_STATIC
#include <glew.h>
#include <iostream>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>
// model class
#include "model.hpp"
#include "shader.hpp"

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
	void render(Model pModel,RenderMode pMode);
	void render(Model pModel);

private:
	Shader* mShader;
};

