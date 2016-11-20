#pragma once
// Inclusion of the OpenGL Wrangler Library
#include <glew.h>
// iostream: Input/Output-Stream
// Used for default input/output functions
#include <iostream>

#include "vector2D.hpp"
#include "vector3D.hpp"

// Declaration of the class: World
// This class controls the major world settings and every object that is created
class World
{
public:
	// Constructor
	World();
	// Destructor
	~World();

	// Add Triangle
	void addTriangle(GLfloat vertices[], GLuint indices[]);
};

