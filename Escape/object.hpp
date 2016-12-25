#pragma once
// Inclusion of the standard I/O library
#include <iostream>
// Inclusion of the standard vector class
#include <vector>
// Inclusion of OpenGLExtentionWrangler
#include <glew.h>
// Inclusion of the OpenGLMath Vector 3x1 
#include <vec3.hpp>


// Declaration of the object class
class Object
{
// All public functions
public:
	/*
	Default Constructor takes 3 different parameters:
	> pVertices: All vertices of the object
	> pIndices: How are the vertices combined
	> pPosition: What is the postion of this object
	*/
	Object(std::vector<float> pVertices, std::vector<unsigned int> pIndices, glm::vec3 pPosition);
	
	// Default Getter Functions
	std::vector<float> getVertices() const;
	std::vector<unsigned int> getIndices() const;
	glm::vec3 getPosition() const;

	// Default Setter Functions
	void setVertices(std::vector<float> pVertices);
	void setIndices(std::vector<unsigned int> pIndices);
	void setPosition(glm::vec3 pPosition);

	// Default Destructor
	~Object();
// All private member of the class
private:
	// Vertices
	std::vector<float> mVertices;
	// Indices
	std::vector<unsigned int> mIndices;
	// Postion
	glm::vec3 mPosition;
};

