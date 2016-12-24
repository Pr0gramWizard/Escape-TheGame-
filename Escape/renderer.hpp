#pragma once

// GLEW
#define GLEW_STATIC
#include <glew.h>
#include <iostream>
// model class
#include "model.hpp"

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
	void render(Model pModel,RenderMode pMode);
	void render(Model pModel);
};

