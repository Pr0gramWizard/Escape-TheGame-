#pragma once
#include <glew.h>
#include <iostream>
#include <vec3.hpp>


class Terrain
{
public:
	Terrain();
	~Terrain();

	// Getter functions
	int getWidth() const;
	int getHeight() const;
	int getDepth() const;

	// Setter functions
	void setWidth(int pWidth);
	void setHeight(int pHeight);
	void setDepth(int pDepth);

private:
	int mWidth;
	int mHeight;
	int mDepth;
	glm::vec3 mStartPoint;
	
};

