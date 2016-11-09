#include "camera.hpp"



Camera::Camera()
{



	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	if (glGetError() != GL_NO_ERROR)
	{
		std::clog << "There was an error starting OpenGL! " << glGetError() << std::endl;
	}

	std::clog << "OpenGL was started successfully!" << std::endl;
}

void Camera::setWindow(Window* pCurrentWindow)
{
	mCurrentWindow = pCurrentWindow;
}



Camera::~Camera()
{
}

void Camera::lookAt(double pFovy, double pAspect, double pZNear, double pZFar)
{
	setFovy(pFovy);
	setAspect(pAspect);
	setZNear(pZNear);
	setZFar(pZFar);
	gluPerspective(getFovy(), getAspect(), getZNear(), getZFar());
}

unsigned int Camera::getCurrentWindowHeight()
{
	return mCurrentWindow->getWindowHeight();
}

unsigned int Camera::getCurrentWindowWidth()
{
	return mCurrentWindow->getWindowWidth();
}

GLdouble Camera::getFovy() const
{
	return mFovy;
}

GLdouble Camera::getAspect() const
{
	return mAspect;
}

GLdouble Camera::getZNear() const
{
	return mZNear;
}

GLdouble Camera::getZFar() const
{
	return mZFar;
}

void Camera::setFovy(GLdouble pFovy)
{
	mFovy = pFovy;
}

void Camera::setAspect(GLdouble pAspect)
{
	mAspect = pAspect;
}

void Camera::setZNear(GLdouble pZNear)
{
	mZNear = pZNear;
}

void Camera::setZFar(GLdouble pZFar)
{
	mZFar = pZFar;
}
