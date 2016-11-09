#pragma once

// Inclusion of the Input/Output stream
#include <iostream>
#include <math.h>
#include "vector3D.hpp"
#include "utility.hpp"


// Defintion of the struct: Matrix4D
// Represents a 4 dimensional matrix with 16 elements
struct Matrix4D
{
	// All the elements of the matrix
	float Elements[4 * 4];

	// Normal constructor
	Matrix4D();

	// Constructor with given diagonal value
	Matrix4D(float pDiagonal);

	// Special matrices:
	// Identity matrix:
	// |1 0 0 0|
	// |0 1 0 0|
	// |0 0 1 0|
	// |0 0 0 1|
	static Matrix4D Identity();
	// Orthographic matrix:
	static Matrix4D Orthographic(float pLeft, float pRight, float pTop, float pBottom, float pNear, float pFar);
	// Perspective matrix
	static Matrix4D Perspective(float pFieldOfView, float pAspectRatio, float pNear, float pFar);

	// Translation of matrix around a given 3D Vector
	static Matrix4D Translation(const Vector3D &pTranslation);
	// Roation of matrix around a given axis with a given angle
	static Matrix4D Rotation(const Vector3D &pAxis, float pAngle);
	// Rescaling the Matrix with a ginven scale
	static Matrix4D Scale(const Vector3D &pScale);
	// Multiplication function
	Matrix4D& multiply(const Matrix4D& pOtherMatrix);
	// Multiplication operator
	friend Matrix4D& operator*(Matrix4D pFirstMatrix, const Matrix4D& pOtherMatrix);
	// Multiplication Assignment operator
	Matrix4D& operator*=(const Matrix4D& pOtherMatrix);

	Matrix4D& lookAt(const Vector3D& Eye, const Vector3D& Center, const Vector3D& Up);

	void Print();
};

