#pragma once
#include <glew.h>
#include <gl/GL.h>
#include <gl\GLU.h>
#include <iostream>
#include <vector>
class cModel
{
public:
	cModel(std::vector<GLfloat> pVertices);
	~cModel();

	void bind();
	void unbind();

	void setVAO(GLuint pVAO);
	GLuint getVAO() const;

private:
	GLuint mVertexArrayObject;
};

