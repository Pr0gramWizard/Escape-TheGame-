#pragma once

#include <gtc\matrix_transform.hpp>
#include <glew.h>
#include <iostream>

class Math {
public:
	/**
	Calculates the height of a position on a triangle

	@param p1, p2, p3: Vertices of the triangle
	@param pos: position on the triangle (x,z)
	@return height at the position
	*/
	static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

	static glm::mat4 getTransformationMatrix(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale);

	static float toRadians(float pAngle);

	static void printMatrix(glm::mat4 pMatrix);
};