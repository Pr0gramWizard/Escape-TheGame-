#pragma once

#include <glew.h>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <vec3.hpp>

class Model
{
public:
	Model();
	~Model();

	

	// Getter
	GLuint getVAO() const;
	GLuint getVertexVBO() const;
	GLuint getIndexVBO() const;
	std::vector<float> getVertices() const;
	std::vector<unsigned int> getIndices() const;
	glm::vec3 getPosition() const;
	glm::mat4 getModelMatrix() const;
	const char* getModelName() const;

	// Setter
	void setVAO(GLuint pVAO);
	void setVertexVBO(GLuint pVBO);
	void setIndexVBO(GLuint pVBO);
	void setVertices(std::vector<float> pVertices);
	void setIndices(std::vector<unsigned int> pIndices);
	void setModelMatrix(glm::vec3 pTranslation, glm::vec3 pRotation, glm::vec3 pScaling);
	void setPosition(glm::vec3 pPosition);
	void setModelName(const char* pModelName);

private:
	GLuint mVAO;
	GLuint mVertexVBO;
	GLuint mIndexVBO;
	std::vector<float> mVertices;
	std::vector<unsigned int> mIndices;
	glm::vec3 mPosition;
	glm::mat4 mModelMatrix;
	const char* mModelName;
	
};

