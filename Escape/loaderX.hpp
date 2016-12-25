#pragma once
#include <iostream>
#include <vector>
#include "object.hpp"
#include "model.hpp"


class LoaderX
{
public:
	LoaderX();
	Model* createModel(Object pObject);

	~LoaderX();

private:
	GLuint createVAO();
	GLuint createVertexVBO(int pAttributeNumber,std::vector<float> pVertices);
	GLuint createIndexVBO(std::vector<unsigned int> pIndices);
	void unbindVAO();

};

