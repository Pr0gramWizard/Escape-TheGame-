#pragma once
#include "shader.hpp"
class EntityShader :
	public Shader
{
public:
	EntityShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	~EntityShader();
	void addAttribute(const char* &pAttributeName);
	void getAllUniformLocations();
	GLuint getUniformLocation(const char* pUniformName);

	void Test();
	
	// Getter Functions
	GLuint getModelMatrixLocation() const;
	GLuint getViewMatrixLocation() const;
	GLuint getProjectionMatrixLocation() const;

	// Setter Functions
	void setModelMatrixLocation(GLuint pModelMatrixLocation);
	void setViewMatrixLocation(GLuint pViewMatrixLocation);
	void setProjectionMatrixLocation(GLuint pProjectionMatrixLocation);

	// Loading specfific uniforms
	void loadModelMatrix(glm::mat4 pMatrix);
	void loadProjectionMatrix(glm::mat4 pMatrix);
	void loadViewMatrix(glm::mat4 pMatrix);

private:
	GLuint mModelMatrixLocation;
	GLuint mViewMatrixLocation;
	GLuint mProjectionMatrixLocation;
};

