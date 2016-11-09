#pragma once
#include <math.h>
// Inclusion of the OpenGL Wrangler Library
#include <glew.h>
// iostream: Input/Output-Stream
// Used for default input/output functions
#include <iostream>

#include "vector2D.hpp"
#include "vector3D.hpp"
#include "cube.hpp"

// Declaration of the class: World
// This class controls the major world settings and every object that is created
class World
{
public:
	// Constructor
	World(unsigned int pMaxNumberOfElements);
	// Destructor
	~World();
	// Init Function
	bool init(unsigned int pWindowWidth, unsigned int pWindowHeight);
	// 2D Graphic function
	bool addTriangle(GLfloat pNumberOfVertices[6], GLfloat pColorOfVertices[9]);
	bool addTriangle(Vector2D pFirstVertex, Vector2D pSecondVertex, Vector2D pThirdVertex);
	bool addQuad(GLfloat pNumberOfVertices[8], GLfloat pColorOfVertices[12]);
	bool addPolygon(GLfloat pNumberOfVertices);
	bool addCircle(GLfloat pRadius);
	void draw();
	// 3D Graphic function
	bool addCube(Cube pCube);
	bool addPyramide();

	void Camera();

	// Setter functions
	void setNumberOfElements(unsigned int pNumberOfElements);
	void setMaxNumberOfElements(unsigned int pMaxNumberOfElements);

	// Getter functions
	unsigned int getNumberOfElements() const;
	unsigned int getMaxNumberOfElements() const;

	// Increase functions
	void increase();
	void decrease();


private:
	unsigned int mNumberOfElements;
	unsigned int mMaxNumberOfElements;
};

