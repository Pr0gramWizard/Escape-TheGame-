#pragma once
// Inclusion of every library
// OpenGLExtensionWrangler library
#include <glew.h>
// Standard Input/Output stream
#include <iostream>
// OpenGLMath Library
// 3x1 Vector
#include <vec3.hpp>
// 4x4 Matrix
#include <mat4x4.hpp>
// Matrix Transformation
#include <gtc/matrix_transform.hpp>

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
const GLfloat FOV = 45.0f;

// Declaration of the camera class
class Camera
{
// All public functions
public:
	// Default constructor
	Camera();
	// Constructor with given parameter:
	// > pPosition: Initial position of the camera
	// > pUp:		The Up vector of the world
	// > pYaw:		Given Yaw
	// > pPitch:	Given Pitch
	Camera(glm::vec3 pPosition, glm::vec3 pUp, GLfloat yaw, GLfloat pitch);

	// Functions that process user input
	void ProcessKeyboard(Camera_Movement pDirection, GLfloat deltaTime);
	GLfloat ProcessMouseMovement(GLfloat pXOffset, GLfloat pYOffset,GLfloat deltaTime);
	void ProcessMouseScroll(GLfloat pYOffset);

	// Returns the current View Matrix
	glm::mat4 GetViewMatrix();
	// Returns the current Projection Matrix
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
	GLfloat getFov() const;


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
	void setFov(GLfloat pFov);



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
	GLfloat mFov;

// All private functions of the class
private:
	void updateCameraVectors();
	static float toRadians(float pAngle);


};

