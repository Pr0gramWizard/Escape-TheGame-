#pragma once

// Inclusion of every important header file
// Input/Output Stream
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
// GLEW Library
#include <glew.h>
// Vector class
#include <vector>
// vec3
#include <vec3.hpp>
// mat4
#include <mat4x4.hpp>
// glm::value_prt
#include <gtc/type_ptr.hpp>
// Light class
#include "../../light/light.hpp"

#define MAX_LIGHTS 4

using namespace std;
// Defintion of the class Shader
class ShadowShader
{
	// All public member of the class 
public:
	// Constructor
	ShadowShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	ShadowShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath, const std::string& pGeometryShaderFilePath);
	// Compile Shader
	void createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	// Bind attribute
	void bindAttribute(GLuint pAttribute, const std::string & pAttributeName);
	// Linking Shader
	void linkShader();
	// Use/Unuse Function
	void use();
	void unuse();
	// Getter Functions
	GLuint getProgramID() const;
	GLuint getVertexShaderID() const;
	GLuint getGeometryShaderID() const;
	GLuint getFragementShaderID() const;
	GLuint getUniformLocation(const char* pUniformName);

	// Setter Functions
	void setProgramID(int pProgramID);
	void setVertexShaderID(int pVertexShaderID);
	void setGeometryShaderID(int pGeometryShaderID);
	void setFragementShaderID(int pFragementShaderID);

	// load uniform variables
	void loadFloat(GLuint pLocation, GLfloat pValue);
	void loadVector(GLuint pLocation, glm::vec3 pVector);
	void loadBool(GLuint pLocation, GLboolean pValue);
	void loadModelMatrix(glm::mat4 pMatrix);
	void loadShadowMatrices(vector<glm::mat4> mShadowTransforms);
	void loadFarplane(GLfloat pFar);
	// Destructor
	~ShadowShader();

	// All private member of the class
private:
	GLuint mProgramID;
	GLuint mVertexShaderID;
	GLuint mFragementShaderID;
	GLuint mGeometryShaderID;
	// All private functions of the class

	//uniform locations
	GLuint mLocation_modelMatrix;
	GLuint mLocation_shadowMatrices[6];
	GLuint mLocation_lightPosition;
	GLuint mLocation_farplane;

private:
	void compileFragementShader(std::string pFragementShaderFilePath);
	void compileVertexShader(std::string pFragementShaderFilePath);
	void compileGeometryShader(std::string pGeometryShaderFilePath);
	void getAllUniformLocations();
	void bindAllAttributes();
	void loadMatrix(GLuint location, glm::mat4 pMatrix);
	void loadVector4f(GLuint pLocation, glm::vec4 pVector);
};

