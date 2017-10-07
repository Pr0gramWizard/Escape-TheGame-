// Inclusion of class declaration
#include "entity.hpp"

// Defaul Constructor
Entity::Entity() {

}

// Constructor
Entity::Entity(glm::vec3 pPosition, glm::vec3 pRotation, GLfloat pScale, Model* pModel)
{
	// Set entity postion
	setPosition(pPosition);
	// Set Entity rotation
	setRotation(pRotation);
	// Set Entity scale
	mScale = pScale;
	// Set Entity Model
	mModel = pModel;

	// std::clog << "Entity was created successfully!" << std::endl;
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
	return mRotation.x;
}

// Returns rotation around y-axis
GLfloat Entity::getYRotation() const
{
	return mRotation.y;
}

// Returns rotation around z-axis
GLfloat Entity::getZRotation() const
{
	return mRotation.z;
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
	return Math::getTransformationMatrix(mPosition, mRotation.x, mRotation.y, mRotation.z, mScale);
}

// Increases position by the given offset
void Entity::increasePosition(glm::vec3 pPosition){
	mPosition = pPosition;
}

// Increases rotation by the given offset
void Entity::increaseXRotation(GLfloat x,GLfloat pDeltaTime){
	mRotation.x += (x*100) * pDeltaTime;
}

// Increases rotation by the given offset
void Entity::increaseYRotation(GLfloat y, GLfloat pDeltaTime) {
	mRotation.y += (y * 100) * pDeltaTime;
}

// Increases rotation by the given offset
void Entity::increaseZRotation(GLfloat z, GLfloat pDeltaTime) {
	mRotation.z += (z * 100) * pDeltaTime;
}

// Sets entity postion
void Entity::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

// Sets entity rotation
void Entity::setRotation(glm::vec3 pRotation)
{
	mRotation = pRotation;
}

void Entity::setModel(Model* pModel){
	mModel = pModel;
}

void Entity::setScale(GLfloat pScale){
	mScale = pScale;
}
