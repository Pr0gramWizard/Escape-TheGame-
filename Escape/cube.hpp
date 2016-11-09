#pragma once

#include <iostream>
#include "vector3D.hpp"

struct Cube
{
public:
	// Normal constructor
	Cube();
	// Constructor with given vertices and rotation
	Cube(float pVertices[108], float pRotation, Vector3D pColor);
	// Destructor
	~Cube();

	// Setter functions
	void setVertices(float pVertices[108]);
	void setColor(float pColor[3]);
	void setColor(Vector3D pColor);
	void setRotation(float pRotation);

	// Getter functions
	float getVertices(int i);
	Vector3D getColor();
	float getRotation() const;

	// Utility functions
	void properties();


// Properties of the cube
private:
	Vector3D mColor;
	float mVertices[108];
	float mRotation;

};

