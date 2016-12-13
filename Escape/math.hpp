#pragma once

#include "vector3D.hpp"
#include "vector2D.hpp"

class Math {
public:
	/**
	Calculates the height of a position on a triangle

	@param p1, p2, p3: Vertices of the triangle
	@param pos: position on the triangle (x,z)
	@return height at the position
	*/
	static float barryCentric(Vector3D p1, Vector3D p2, Vector3D p3, Vector2D pos);

};