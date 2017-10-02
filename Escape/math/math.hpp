#pragma once
#define _USE_MATH_DEFINES

// OpenGLMath extra functions
#include <gtc\matrix_transform.hpp>
// OpenGLExtensionWrangler
#include <glew.h>
// Standard Input/Output Stream
#include <iostream>
// Vector
#include <vector>
// Random 
#include <random>
#include <math.h>
class Math {
public:
	/**
	Calculates the height of a position on a triangle

	@param p1, p2, p3: Vertices of the triangle
	@param pos: position on the triangle (x,z)
	@return height at the position
	*/
	static float barryCentricHeight(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

	// Returns a transformation matrix
	static glm::mat4 getTransformationMatrix(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale);

	static glm::mat4 Math::getTransformationMatrix(glm::vec2 pTranslation, glm::vec2 pScale);

	// Converts an angle from degree to radian
	static float toRadians(float pAngle);

	// Prints out a 4x4 Matrix
	static void printMatrix(glm::mat4 pMatrix);

	// Returns max int value
	static int max(int a, int b);

	// Returns min int value
	static int min(int a, int b);

	// Generates random number in given intervall
	static int getRand(int startIntervall, int endIntervall);

	// Generates random value between -1 and 1
	static float getNoise(int x, int z);

	// Returns random value between -1 and 1 with averaged corners
	static float getSmoothNoise(int x, int z);

	// Returns random value between -1 and 1 with averaged corners
	static float getInterpolatedNoise(float x, float z);

	// Interpolate between two floats
	static float interpolate(float a, float b, float blendFactor);
	// Prints nested Vectors
	static void printNestedVector(std::vector<std::vector<int> > pVector);

};