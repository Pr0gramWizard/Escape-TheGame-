#pragma once

#include <glm.hpp>
#include <glew.h>

class Player {

public:
	Player(glm::vec3 pPosition, glm::vec3 pVelocity, GLfloat pHeight, const char* pName);
	//velocity is set to 0
	Player(glm::vec3 pPosition, GLfloat pHeight, const char* pName);

	void move();

	//adds offset to position
	void setPosition(glm::vec3 pOffset);
	//sets position to absolute value
	void setPositionAbsolute(glm::vec3 pPosition);
	void setVelocity(glm::vec3 pVelocity);
	void setHeight(GLfloat pHeight);
	void setName(const char* pName);

	glm::vec3 getPosition() const;
	glm::vec3 getVelocity() const;
	GLfloat getHeight() const;
	const char* getName() const;

private:
	glm::vec3 mPosition;
	glm::vec3 mVelocity;
	//used for camera position and collision
	GLfloat mHeight;
	const char* mName;
};