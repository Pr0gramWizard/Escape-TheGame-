#pragma once

#include <vec3.hpp>
#include <mat4x4.hpp>
#include "math.hpp"
#include <glew.h>
#include "model.hpp"

class Entity
{
public:
	Entity(glm::vec3 pPosition, GLfloat pXRotation, GLfloat pYRotation, GLfloat pZRotation, GLfloat pScale, Model* pModel);
	~Entity();

	glm::vec3 getPosition() const;
	GLfloat getXRotation() const;
	GLfloat getYRotation() const;
	GLfloat getZRotation() const;
	GLfloat getScale() const;
	Model* getModel();

	glm::mat4 getModelMatrix();

	void increasePosition(GLfloat x, GLfloat y, GLfloat z);
	void increaseRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat pDeltaTime);

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
	Model* mModel;
};

