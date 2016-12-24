#include "math.hpp"

float Math::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

glm::mat4 Math::getTransformationMatrix(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, pPosition);
	matrix = glm::rotate(matrix, Math::toRadians(pXRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, Math::toRadians(pYRotation), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, Math::toRadians(pZRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::scale(matrix, glm::vec3(pScale, pScale, pScale));
	return matrix;
}

float Math::toRadians(float pAngle)
{
	float PI = 3.14159265358979323846f;
	return pAngle * (PI / 180.0f);
}
