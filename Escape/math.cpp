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
	glm::mat4 translate;
	translate = glm::translate(translate, pPosition);
	glm::mat4 rotationX;
	rotationX = glm::rotate(rotationX, Math::toRadians(pXRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY;
	rotationY = glm::rotate(rotationY, Math::toRadians(pYRotation), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ;
	rotationZ = glm::rotate(rotationZ, Math::toRadians(pZRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scale;
	scale = glm::scale(scale, glm::vec3(pScale, pScale, pScale));
	glm::mat4 rotation = rotationX * rotationY * rotationZ;
	// return translate * rotation * scale;
	return translate;
}

float Math::toRadians(float pAngle)
{
	float PI = 3.14159265358979323846f;
	return pAngle * (PI / 180.0f);
}

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
