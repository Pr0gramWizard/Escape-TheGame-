#pragma once

// Vector 
#include <vec3.hpp>
// Matrix (4x4) 
#include <mat4x4.hpp>
// Own Math class
#include "../math/math.hpp"
// OpenGLExtensionWrangler
#include <glew.h>
// Model class
#include "../model/model.hpp"

// Declaration of Entity class
class Entity
{
// All public functions of the class
public:
	// Constructor
	Entity(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale, Model* pModel);
	// Destructor
	~Entity();

	// Getter functions
	glm::vec3 getPosition() const;
	GLfloat getXRotation() const;
	GLfloat getYRotation() const;
	GLfloat getZRotation() const;
	GLfloat getScale() const;
	Model* getModel();
	glm::mat4 getModelMatrix();

	// Increases position of the entity
	void increasePosition(GLfloat x, GLfloat y, GLfloat z);
	// Increases rotation of the entity
	void increaseRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat pDeltaTime);

	// Set Positon of the entity
	void setPosition(glm::vec3 pPosition);
	// Set Rotation of the entity
	void setRotation(GLfloat x, GLfloat y, GLfloat z);

// All private member of the class
private:
	// Entity Postion
	glm::vec3 mPosition;
	// Entity Rotation
	GLfloat mXRotation;
	GLfloat mYRotation;
	GLfloat mZRotation;
	//  Entity Scale ( 1 = Original size)
	GLfloat mScale;
	// Pointer to model class
	Model* mModel;
};

