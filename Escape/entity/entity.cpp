#include "entity.hpp"

// constructor
Entity::Entity(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale, Model* pModel)
{
	setPosition(pPosition);
	setRotation(pXRotation, pYRotation, pZRotation);
	mScale = pScale;
	mModel = pModel;
}

// destructor
Entity::~Entity()
{
}

// returns position
glm::vec3 Entity::getPosition() const
{
	return mPosition;
}

// returns rotation around x-axis
GLfloat Entity::getXRotation() const
{
	return mXRotation;
}

// returns rotation around y-axis
GLfloat Entity::getYRotation() const
{
	return mYRotation;
}

// returns rotation around z-axis
GLfloat Entity::getZRotation() const
{
	return mZRotation;
}

// returns scale
GLfloat Entity::getScale() const
{
	return mScale;
}

// returns model
Model * Entity::getModel()
{
	return mModel;
}

// calculates modelmatrix and returns it
glm::mat4 Entity::getModelMatrix()
{
	return Math::getTransformationMatrix(mPosition, mXRotation, mYRotation, mZRotation, mScale);
}

// increases position by the given offset
void Entity::increasePosition(GLfloat x, GLfloat y, GLfloat z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}

// increases rotation by the given offset
void Entity::increaseRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat pDeltaTime)
{
	mXRotation += (x*100) * pDeltaTime;
	mYRotation += (y*100) * pDeltaTime;
	mZRotation += (z*100) * pDeltaTime;
}

// sets position
void Entity::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

// sets rotation
void Entity::setRotation(GLfloat x, GLfloat y, GLfloat z)
{
	mXRotation = x;
	mYRotation = y;
	mZRotation = z;
}