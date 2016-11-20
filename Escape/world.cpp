#include "world.hpp"



World::World()
{
	std::clog << "World was created successfully!" << std::endl;
	glewInit();
}

void World::addTriangle(GLfloat vertices[], GLuint indices[])
{
	// Creating new Variables to store the objects
	GLuint VertexBufferObject, VertexArrayObject, ElementBufferObject;

	// Generating the objects
	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glGenBuffers(1, &ElementBufferObject);

	// Binding the vertex array object
	glBindVertexArray(VertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Unbind VAO 
	glBindVertexArray(0); 


}


World::~World()
{
	std::clog << "World was destroyed successfully!" << std::endl;
}


