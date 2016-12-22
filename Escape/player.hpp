#pragma once

#include <glm.hpp>
#include <glew.h>

class Player {

public:
	static const GLfloat MOVESPEED;
	static const GLfloat TURNSPEED;
	static const GLfloat GRAVITY;
	//needed?
	static const GLfloat JUMPPOWER;

public:
	Player(glm::vec3 pPosition, GLfloat pHeight, const char* pName);

	void move();

	//adds offset to position
	void incPosition(glm::vec3 pOffset);
	//sets position to absolute value
	void setPosition(glm::vec3 pPosition);
	void setHeight(GLfloat pHeight);
	void setName(const char* pName);

	glm::vec3 getPosition() const;
	GLfloat getHeight() const;
	const char* getName() const;

private:
	glm::vec3 mPosition;
	//used for camera position and collision
	GLfloat mHeight;
	GLfloat mCurrentMoveSpeed;
	GLfloat mCurrentTurnSpeed;
	//add vec3 viewDirection?
	const char* mName;
};