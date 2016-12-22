#pragma once

// GLEW
#define GLEW_STATIC
#include <glew.h>
// model class
#include "model.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void prepare();
	void render(Model pModel);
};

