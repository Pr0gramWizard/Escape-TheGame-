#pragma once

#include <iostream>
#include <glew.h>
#include "vector3D.hpp"
#include "vector4D.hpp"

struct Cube
{
public:
	// Normal constructor
	Cube();
	// Constructor with given vertices and rotation
	//Cube(GLfloat pVertices[8][3], GLfloat pSides[6][4], float pRotation, Vector3D pColor);

	// Constructor with given vertices and sides
	Cube(GLfloat pVertices[24], GLfloat pSides[6][4]);
	// Destructor
	~Cube();

	// Setter functions
	void setVerticesVector3D(Vector3D pVertices, int pPosition);
	void setVertices(GLfloat pVertices[24]);
	void setSide(GLfloat pSide[4], int pPosition);
	void setSides(GLfloat pSides[6][4]);
	void setColor(GLfloat pColor[3]);
	void setColor(Vector3D pColor);
	void setRotation(GLfloat pRotation);

	// Getter functions
	GLfloat getVertices(int i);
	Vector3D getVerticesVector3D(int i);
	GLfloat getSides(int i, int j);
	Vector4D getSidesVector4D(int i);
	Vector3D getColor();
	GLfloat getRotation() const;

	// Utility functions
	void properties();


// Properties of the cube
private:
	Vector3D mColor;
	GLfloat mVertices[24];
	GLfloat mSides[6][4];
	GLfloat mRotation;

};

