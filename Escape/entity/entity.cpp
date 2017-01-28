// Inclusion of class declaration
#include "entity.hpp"

// Constructor
Entity::Entity(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale, Model* pModel)
{
	// Set entity postion
	setPosition(pPosition);
	// Set Entity rotation
	setRotation(pXRotation, pYRotation, pZRotation);
	// Set Entity scale
	mScale = pScale;
	// Set Entity Model
	mModel = pModel;

	std::clog << "Entity was created successfully!" << std::endl;
}

// Destructor
Entity::~Entity()
{
	std::clog << "Entity was destroyed successfully!" << std::endl;
}

// Returns position
glm::vec3 Entity::getPosition() const
{
	return mPosition;
}

// Returns rotation around x-axis
GLfloat Entity::getXRotation() const
{
	return mXRotation;
}

// Returns rotation around y-axis
GLfloat Entity::getYRotation() const
{
	return mYRotation;
}

// Returns rotation around z-axis
GLfloat Entity::getZRotation() const
{
	return mZRotation;
}

// Returns scale
GLfloat Entity::getScale() const
{
	return mScale;
}

// Returns model
Model * Entity::getModel()
{
	return mModel;
}

// Calculates modelmatrix and returns it
glm::mat4 Entity::getModelMatrix()
{
	return Math::getTransformationMatrix(mPosition, mXRotation, mYRotation, mZRotation, mScale);
}

// Increases position by the given offset
void Entity::increasePosition(GLfloat x, GLfloat y, GLfloat z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}

// Increases rotation by the given offset
void Entity::increaseRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat pDeltaTime)
{
	mXRotation += (x*100) * pDeltaTime;
	mYRotation += (y*100) * pDeltaTime;
	mZRotation += (z*100) * pDeltaTime;
}

// Sets entity postion
void Entity::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

// Sets entity rotation
void Entity::setRotation(GLfloat x, GLfloat y, GLfloat z)
{
	mXRotation = x;
	mYRotation = y;
	mZRotation = z;
}
