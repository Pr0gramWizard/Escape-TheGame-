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
	Entity();
	// Constructor
	Entity(glm::vec3 pPosition, glm::vec3 pRotation, GLfloat pScale, Model* pModel);
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
	void increasePosition(glm::vec3 pPosition);
	// Increases rotation of the entity
	void increaseXRotation(GLfloat x, GLfloat pDeltaTime);
	void increaseYRotation(GLfloat y,GLfloat pDeltaTime);
	void increaseZRotation(GLfloat z, GLfloat pDeltaTime);

	// Set Positon of the entity
	void setPosition(glm::vec3 pPosition);
	// Set Rotation of the entity
	void setRotation(glm::vec3 pRotation);
	// Set Model
	void setModel(Model* pModel);
	// Set Scale
	void setScale(GLfloat pScale);

// All private member of the class
private:
	// Entity Postion
	glm::vec3 mPosition;
	// Entity Rotation
	glm::vec3 mRotation;
	//  Entity Scale ( 1 = Original size)
	GLfloat mScale;
	// Pointer to model class
	Model* mModel;
};

