#pragma once

#include <vec3.hpp>
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

	void increasePosition(GLfloat x, GLfloat y, GLfloat z);
	void increaseRotation(GLfloat x, GLfloat y, GLfloat z);

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

