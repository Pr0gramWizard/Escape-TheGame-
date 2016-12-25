#include "entity.hpp"

Entity::Entity(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale, Model* pModel)
{
	setPosition(pPosition);
	setRotation(pXRotation, pYRotation, pZRotation);
	mScale = pScale;
	mModel = pModel;
}

Entity::~Entity()
{
}

glm::vec3 Entity::getPosition() const
{
	return mPosition;
}

GLfloat Entity::getXRotation() const
{
	return mXRotation;
}

GLfloat Entity::getYRotation() const
{
	return mYRotation;
}

GLfloat Entity::getZRotation() const
{
	return mZRotation;
}

GLfloat Entity::getScale() const
{
	return mScale;
}

Model * Entity::getModel()
{
	return mModel;
}

glm::mat4 Entity::getModelMatrix()
{
	return Math::getTransformationMatrix(mPosition, mXRotation, mYRotation, mZRotation, mScale);
}

void Entity::increasePosition(GLfloat x, GLfloat y, GLfloat z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}

void Entity::increaseRotation(GLfloat x, GLfloat y, GLfloat z)
{
	mXRotation += x;
	mYRotation += y;
	mZRotation += z;
}

void Entity::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

void Entity::setRotation(GLfloat x, GLfloat y, GLfloat z)
{
	mXRotation = x;
	mYRotation = y;
	mZRotation = z;
}
