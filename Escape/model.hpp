#pragma once

#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <iostream>
#include <vec3.hpp>

class Model
{
public:
	Model(int pVaoId, int pVertices, glm::vec3 pPosition);
	~Model();

	int getVaoId();
	int getVerticesCount();
	glm::mat4 getModelMatrix() const;

	// Getter
	glm::vec3 getPosition() const;

	// Setter
	void setPosition(glm::vec3 pPosition);

private:
	int mVaoId;
	int mVertices;
	glm::vec3 mPosition;
	
};

