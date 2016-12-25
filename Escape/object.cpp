#include "object.hpp"

Object::Object(std::vector<float> pVertices, std::vector<unsigned int> pIndices, glm::vec3 pPosition)
{
	// Log Message
	std::cout << "Object class was started succesfully!" << std::endl;
	// Setting the vertices
	setVertices(pVertices);
	// Setting the indices
	setIndices(pIndices);
	// Setting the position
	setPosition(pPosition);

}

Object::~Object()
{
}

std::vector<float> Object::getVertices() const
{
	return mVertices;
}

std::vector<unsigned int> Object::getIndices() const
{
	return mIndices;
}

glm::vec3 Object::getPosition() const
{
	return mPosition;
}

void Object::setVertices(std::vector<float> pVertices)
{
	mVertices = pVertices;
}

void Object::setIndices(std::vector<unsigned int> pIndices)
{
	mIndices = pIndices;
}

void Object::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}
