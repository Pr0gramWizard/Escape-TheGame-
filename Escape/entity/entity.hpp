#pragma once

// vector class
#include <vec3.hpp>
// matrix class
#include <mat4x4.hpp>
// maths
#include "../math/math.hpp"
// glew
#include <glew.h>
// model class
#include "../model/model.hpp"
#include "../model/cmodel.hpp"

class Entity
{
public:
	// constructor
	Entity(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale, Model* pModel);
	Entity(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale, cModel* pModel);
	// destructor
	~Entity();

	// getters
	glm::vec3 getPosition() const;
	GLfloat getXRotation() const;
	GLfloat getYRotation() const;
	GLfloat getZRotation() const;
	GLfloat getScale() const;
	Model* getModel();

	glm::mat4 getModelMatrix();

	// increases position or rotation of the entity
	void increasePosition(GLfloat x, GLfloat y, GLfloat z);
	void increaseRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat pDeltaTime);

	// sets position or rotation of entity
	void setPosition(glm::vec3 pPosition);
	void setRotation(GLfloat x, GLfloat y, GLfloat z);


private:
	// position
	glm::vec3 mPosition;
	// rotation in degrees
	GLfloat mXRotation;
	GLfloat mYRotation;
	GLfloat mZRotation;
	//  scale (1 = normal size)
	GLfloat mScale;
	// model
	Model* mModel;
	cModel* mCModel;
};

