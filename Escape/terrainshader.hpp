#pragma once
// Inclusion of every important header file
// Input/Output Stream
#include <iostream>
// GLEW Library
#include <glew.h>
// File Stream
#include <fstream>
// String class
#include <string>
// Vector class
#include <vector>
// vec3
#include <vec3.hpp>
// mat4
#include <mat4x4.hpp>
// glm::value_prt
#include <gtc/type_ptr.hpp>


// Defintion of the class Shader
class TerrainShader
{
// All public member of the class 
public:
	// Constructor
	TerrainShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	~TerrainShader();
	// Compile Shader
	void createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	// Bind attribute
	void bindAttribute(GLuint pAttribute, const std::string & pAttributeName);
	// Automatic binds all important attributes
	void bindAllAttributes();
	// Linking Shader
	void linkShader();
	// Use/Unuse Function
	void use();
	void unuse();
	// Getter Functions
	GLuint getProgramID() const;
	GLuint getVertexShaderID() const;
	GLuint getFragementShaderID() const;
	GLuint getUniformLocation(const char* pUniformName);

	// Setter Functions
	void setProgramID(int pProgramID);
	void setVertexShaderID(int pVertexShaderID);
	void setFragementShaderID(int pFragementShaderID);

	// load uniform variables
	void loadFloat(GLuint pLocation, GLfloat pValue);
	void loadVector(GLuint pLocation, glm::vec3 pVector);
	void loadBool(GLuint pLocation, GLboolean pValue);
	void getAllUniformLocations();
	void loadMatrix(GLuint location, glm::mat4 pMatrix);
	
	// Set uniform matrix location
	void setModelMatrixLocation(GLuint pModelMatrixLocation);
	void setViewMatrixLocation(GLuint pViewMatrixLocation);
	void setProjectionMatrixLocation(GLuint pProjectionMatrixLocation);
	// Get uniform matrix location
	GLuint getModelMatrixLocation() const;
	GLuint getViewMatrixLocation() const;
	GLuint getProjectionMatrixLocation() const;

	// Load uniform matrix
	void loadModelMatrix(glm::mat4 pMatrix);
	void loadProjectionMatrix(glm::mat4 pMatrix);
	void loadViewMatrix(glm::mat4 pMatrix);
// All private member of the class
private:
		GLuint mProgramID;
		GLuint mVertexShaderID;
		GLuint mFragementShaderID;
		GLuint mModelMatrixLocation;
		GLuint mViewMatrixLocation;
		GLuint mProjectionMatrixLocation;
// All private functions of the class
private:
	void compileFragementShader(std::string pFragementShaderFilePath);
	void compileVertexShader(std::string pFragementShaderFilePath);
};