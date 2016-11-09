#pragma once
#include <glew.h>
#include <iostream>
#include "window.hpp"
class Camera
{
public:
	Camera();

	~Camera();

	void setWindow(Window* pCurrentWindow);
	void lookAt(double pFovy,double pAspect,double mZNear,double mZFar);

	// Getter Function
	unsigned int getCurrentWindowHeight();
	unsigned int getCurrentWindowWidth();
	GLdouble getFovy() const;
	GLdouble getAspect() const;
	GLdouble getZNear() const;
	GLdouble getZFar() const;

	// Setter functions
	void setFovy(GLdouble);
	void setAspect(GLdouble);
	void setZNear(GLdouble);
	void setZFar(GLdouble);



private:
	GLdouble mFovy;
	GLdouble mAspect;
	GLdouble mZNear;
	GLdouble mZFar;
	Window* mCurrentWindow;



};

