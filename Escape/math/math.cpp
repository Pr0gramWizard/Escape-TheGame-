// Inclusion of class declaration
#include "math.hpp"

// Calculates the height of a position on a triangle
float Math::barryCentricHeight(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	// std::cout << det << std::endl;
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	// std::cout << l1 << std::endl;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	// std::cout << l2 << std::endl;
	float l3 = 1.0f - l1 - l2;
	// std::cout << l3 << std::endl;
	// std::cout << l1 * p1.y + l2 * p2.y + l3 * p3.y << std::endl;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

// Returns a transformation matrix
glm::mat4 Math::getTransformationMatrix(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale)
{
	// Creates translation matrix
	glm::mat4 translate;
	// Translates around given position
	translate = glm::translate(translate, pPosition);
	// Rotates around X axis
	glm::mat4 rotationX;
	rotationX = glm::rotate(rotationX, Math::toRadians(pXRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	// Rotate around Y axis
	glm::mat4 rotationY;
	rotationY = glm::rotate(rotationY, Math::toRadians(pYRotation), glm::vec3(0.0f, 1.0f, 0.0f));
	// Rotate around Z axis
	glm::mat4 rotationZ;
	rotationZ = glm::rotate(rotationZ, Math::toRadians(pZRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	// Create scale matrix
	glm::mat4 scale;
	// Scale by given factor
	scale = glm::scale(scale, glm::vec3(pScale, pScale, pScale));
	// Build final rotation matrix
	glm::mat4 rotation = rotationX * rotationY * rotationZ;

	// Return transformation matrix
	return translate * rotation * scale;
}

// Converts angle from degree to radian
float Math::toRadians(float pAngle)
{
	float PI = 3.14159265358979323846f;
	return pAngle * (PI / 180.0f);
}

// Prints matrix in console
void Math::printMatrix(glm::mat4 pMatrix)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << pMatrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

// Returns max value
int Math::max(int a, int b) {
	return (a < b) ? b : a;
}

// Returns min value
int Math::min(int a, int b) {
	return (a < b) ? a : b;
}

// Generate random number in given interval
int Math::getRand(int startValue, int endValue) {
	const int range_from = startValue;
	const int range_to = endValue;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(range_from, range_to);

	return distr(generator);
}

// Interpolate between two floats
float Math::interpolate(float a, float b, float blendFactor) {
	double theta = blendFactor * M_PI;
	float f = (1.0f - (float) cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

// Interpolate between two floats (different algorithm)
float Math::lerp(float a, float b, float t) {
	return (1.0f - t) * a + t * b;
}

// Inverse Interpolate between two floats and the interpolated result
float Math::inverseLerp(float a, float b, float y) {
	if (a != b) {
		return (a - y) / (a - b);
	}
	else {
		std::cout << "Inverse Lerp failed because a == b!" << std::endl;
		return 1.0f;
	}
}

// Generate random noise which is interpolated
float Math::getInterpolatedNoise(float x, float z) {
	int intPartX = (int)x;
	int intPartZ = (int)z;

	float fracX = x - intPartX;
	float fracZ = z - intPartZ;

	float v1 = Math::getSmoothNoise(intPartX, intPartZ);
	float v2 = Math::getSmoothNoise(intPartX + 1, intPartZ);
	float v3 = Math::getSmoothNoise(intPartX, intPartZ + 1);
	float v4 = Math::getSmoothNoise(intPartX + 1, intPartZ + 1);

	float i12 = Math::interpolate(v1, v2, fracX);
	float i34 = Math::interpolate(v3, v4, fracX);

	return Math::interpolate(i12, i34, fracZ);
}

// Generate random value between -1 and 1
float Math::getNoise(int x, int z) {
	const float range_from = -1.0;
	const float range_to = 1.0;
	std::random_device                  rand_dev;
	std::mt19937                        generator(x * 18289 + z * 38729 * rand_dev());
	std::uniform_real_distribution<float>  distr(range_from, range_to);
	return distr(generator);
}

// Generate random value between -1 and 1
float Math::getSmoothNoise(int x, int z) {
	float corners = (Math::getNoise(x - 1, z - 1) + Math::getNoise(x + 1, z - 1) + Math::getNoise(x - 1, z + 1) + Math::getNoise(x + 1, z + 1) / 16.0f);
	float sides = (Math::getNoise(x - 1, z) + Math::getNoise(x + 1, z) + Math::getNoise(x, z + 1) + Math::getNoise(x , z - 1) / 8.0f);
	float center = (Math::getNoise(x, z) / 4.0f);

	return corners + sides + center;
}

// Floor float number to a given digit
float Math::round(float x, int digit) {
	return 	floor(x*pow(10, digit)) / pow(10, digit);
}
