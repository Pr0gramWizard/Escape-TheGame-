#pragma once
#include <glew.h>
#include <iostream>
#include <vec3.hpp>
#include "matrix4D.hpp"
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
// #include "utility.hpp"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 5.0f;
const GLfloat SENSITIVTY = 0.1f;
const GLfloat ZOOM = 45.0f;


class Camera
{
public:
	Camera();
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	void ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset);
	void ProcessMouseScroll(GLfloat pYOffset);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(int pHeight, int pWidth);


	// Getter Functions
	glm::vec3 getPosition() const;
	glm::vec3 getFront() const;
	glm::vec3 getUp() const;
	glm::vec3 getRight() const;
	glm::vec3 getWorldUp() const;

	GLfloat getYaw() const;
	GLfloat getPitch() const;
	GLfloat getMovementSpeed() const;
	GLfloat getMouseSensitivity() const;
	GLfloat getZoom() const;


	// Setter Functions
	void setPosition(glm::vec3 pPosition);
	void setFront(glm::vec3 pFront);
	void setUp(glm::vec3 pUp);
	void setRight(glm::vec3 pRight);
	void setWorldUp(glm::vec3 pWorldUp);

	void setYaw(GLfloat pYaw);
	void setPitch(GLfloat pPitch);
	void setMovementSpeed(GLfloat pMovementSpeed);
	void setMouseSensitivity(GLfloat pMouseSensitivity);
	void setZoom(GLfloat pZoom);



// All private members of the class
private:
	// Camera Attributes
	glm::vec3 mPosition;
	glm::vec3 mFront;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mWorldUp;
	// Eular Angles
	GLfloat mYaw;
	GLfloat mPitch;
	// Camera options
	GLfloat mMovementSpeed;
	GLfloat mMouseSensitivity;
	GLfloat mZoom;

// All private functions of the class
private:
	void updateCameraVectors();
	static float toRadians(float pAngle);


};

