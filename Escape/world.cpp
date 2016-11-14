#include "world.hpp"



World::World(unsigned int pMaxNumberOfElements)
{
	std::clog << "World was created successfully!" << std::endl;
	setMaxNumberOfElements(pMaxNumberOfElements);
	glewInit();
}


World::~World()
{
	std::clog << "World was destroyed successfully!" << std::endl;
}

bool World::init(unsigned int pWindowWidth, unsigned int pWindowHeight)
{
	glClearColor(1, 1, 1, 1);

	
	

	return true;

}

bool World::addTriangle(GLfloat pNumberOfVertices[6], GLfloat pColorOfVertices[9])
{
	increase();
	GLuint VertexBufferID;
	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pNumberOfVertices), pNumberOfVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	

	/*
	glColor3f(pColorOfVertices[0], pColorOfVertices[1], pColorOfVertices[2]);
	glBegin(GL_TRIANGLES);
	glVertex2f(pNumberOfVertices[0], pNumberOfVertices[1]);
	glColor3f(pColorOfVertices[3], pColorOfVertices[4], pColorOfVertices[5]);
	glVertex2f(pNumberOfVertices[2], pNumberOfVertices[3]);
	glColor3f(pColorOfVertices[6], pColorOfVertices[7], pColorOfVertices[8]);
	glVertex2f(pNumberOfVertices[4], pNumberOfVertices[5]);
	glEnd();
	glFlush();
	*/

	return true;
}

bool World::addTriangle(Vector2D pFirstVertex, Vector2D pSecondVertex, Vector2D pThirdVertex)
{
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(pFirstVertex.x, pFirstVertex.y);
	glVertex2f(pSecondVertex.x, pSecondVertex.y);
	glVertex2f(pThirdVertex.x, pThirdVertex.y);
	glEnd();
	glFlush();
	
	return true;
}

void World::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool World::addQuad(GLfloat pNumberOfVertices[8], GLfloat pColorOfVertices[12])
{
	glBegin(GL_QUADS);
	glColor3f(pColorOfVertices[0], pColorOfVertices[1], pColorOfVertices[2]);
	glVertex2f(pNumberOfVertices[0],pNumberOfVertices[1]);
	glColor3f(pColorOfVertices[3], pColorOfVertices[4], pColorOfVertices[5]);
	glVertex2f(pNumberOfVertices[2], pNumberOfVertices[3]);
	glColor3f(pColorOfVertices[6], pColorOfVertices[7], pColorOfVertices[8]);
	glVertex2f(pNumberOfVertices[4], pNumberOfVertices[5]);
	glColor3f(pColorOfVertices[9], pColorOfVertices[10], pColorOfVertices[11]);
	glVertex2f(pNumberOfVertices[6], pNumberOfVertices[7]);
	glEnd();
	return true;
}

bool World::addPolygon(GLfloat pNumberofVertices)
{
	return false;
}

bool World::addCircle(GLfloat pRadius)
{
	return true;
}

bool World::addCube(Cube pCube)
{
	
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// glRotatef(pCube.getRotation(), 0.0f, 0.0f, -4.0f);

	

	return true;

}



void World::Camera()
{
	Vector3D cameraPos(0.0f, 0.0f, 3.0f);
	Vector3D cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3D cameraDirection = cameraPos.normalize() - cameraTarget.normalize();

}

void World::showCoordinateSystem()
{
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);

	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);


	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();
}


bool World::addPyramide()
{
	return false;
}

void World::setNumberOfElements(unsigned int pNumberOfElements)
{
	mNumberOfElements = pNumberOfElements;
}

void World::setMaxNumberOfElements(unsigned int pMaxNumberOfElements)
{
	mMaxNumberOfElements = pMaxNumberOfElements;
}

unsigned int World::getNumberOfElements() const
{
	return mNumberOfElements;
}

unsigned int World::getMaxNumberOfElements() const
{
	return mMaxNumberOfElements;
}

void World::increase()
{
	mNumberOfElements++;
}

void World::decrease()
{
	mNumberOfElements--;
}
