#pragma once
#include <glew.h>
#include <iostream>
#include "vector3D.hpp"
#include "matrix4D.hpp"
#include "utility.hpp"

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
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;


class Camera
{
public:
	Camera();
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	void ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset);
	void ProcessMouseScroll(GLfloat pYOffset);

	Matrix4D GetViewMatrix();


	// Getter Functions
	Vector3D getPosition() const;
	Vector3D getFront() const;
	Vector3D getUp() const;
	Vector3D getRight() const;
	Vector3D getWorldUp() const;

	GLfloat getYaw() const;
	GLfloat getPitch() const;
	GLfloat getMovementSpeed() const;
	GLfloat getMouseSensitivity() const;
	GLfloat getZoom() const;


	// Setter Functions
	void setPosition(Vector3D pPosition);
	void setFront(Vector3D pFront);
	void setUp(Vector3D pUp);
	void setRight(Vector3D pRight);
	void setWorldUp(Vector3D pWorldUp);

	void setYaw(GLfloat pYaw);
	void setPitch(GLfloat pPitch);
	void setMovementSpeed(GLfloat pMovementSpeed);
	void setMouseSensitivity(GLfloat pMouseSensitivity);
	void setZoom(GLfloat pZoom);



// All private members of the class
private:
	// Camera Attributes
	Vector3D mPosition;
	Vector3D mFront;
	Vector3D mUp;
	Vector3D mRight;
	Vector3D mWorldUp;
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



};

