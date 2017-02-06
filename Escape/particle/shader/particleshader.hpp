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

#define MAX_LIGHTS 6

using namespace std;
// Defintion of the class Shader
class ParticleShader
{
	// All public member of the class 
public:
	// Constructor
	ParticleShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	ParticleShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath, const std::string& pGeometryShaderFilePath);
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
	void loadProjectionMatrix(glm::mat4 pMatrix);
	void loadViewMatrix(glm::mat4 pMatrix);
	void loadLights(vector<Light*> pLights, bool pDiscoTime);
	void loadPlane(glm::vec4 pVector);
	void loadFogData(GLfloat pDensity, GLfloat pGradient);
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);
	void loadPlayerBelowLake(GLfloat pPlayerBelowLake);
	// Destructor
	~ParticleShader();

	// Particle Setter
	// Setting vectors
	void SetUniform(string sName, glm::vec2* vVectors, int iCount = 1);
	void SetUniform(string sName, const glm::vec2 vVector);
	void SetUniform(string sName, glm::vec3* vVectors, int iCount = 1);
	void SetUniform(string sName, const glm::vec3 vVector);
	void SetUniform(string sName, glm::vec4* vVectors, int iCount = 1);
	void SetUniform(string sName, const glm::vec4 vVector);

	// Setting floats
	void SetUniform(string sName, float* fValues, int iCount = 1);
	void SetUniform(string sName, const float fValue);

	// Setting 3x3 matrices
	void SetUniform(string sName, glm::mat3* mMatrices, int iCount = 1);
	void SetUniform(string sName, const glm::mat3 mMatrix);

	// Setting 4x4 matrices
	void SetUniform(string sName, glm::mat4* mMatrices, int iCount = 1);
	void SetUniform(string sName, const glm::mat4 mMatrix);

	// Setting integers
	void SetUniform(string sName, int* iValues, int iCount = 1);
	void SetUniform(string sName, const int iValue);

	// Model and normal matrix setting ispretty common
	void SetModelAndNormalMatrix(string sModelMatrixName, string sNormalMatrixName, glm::mat4 mModelMatrix);
	void SetModelAndNormalMatrix(string sModelMatrixName, string sNormalMatrixName, glm::mat4* mModelMatrix);

	// All private member of the class
private:
	GLuint mProgramID;
	GLuint mVertexShaderID;
	GLuint mFragementShaderID;
	GLuint mGeometryShaderID;
	// All private functions of the class

	//uniform locations
	GLuint mLocation_modelMatrix;
	GLuint mLocation_projectionMatrix;
	GLuint mLocation_viewMatrix;
	GLuint mLocation_lightPosition[MAX_LIGHTS];
	GLuint mLocation_lightColor[MAX_LIGHTS];
	GLuint mLocation_lightAttenuation[MAX_LIGHTS];
	GLuint mLocation_plane;
	GLuint mLocation_fogDensity;
	GLuint mLocation_fogGradient;
	GLuint mLocation_backgroundColor;
	GLuint mLocation_playerBelowLake;

private:
	void compileFragementShader(std::string pFragementShaderFilePath);
	void compileVertexShader(std::string pFragementShaderFilePath);
	void compileGeometryShader(std::string pGeometryShaderFilePath);
	void getAllUniformLocations();
	void bindAllAttributes();
	void loadMatrix(GLuint location, glm::mat4 pMatrix);
	void loadVector4f(GLuint pLocation, glm::vec4 pVector);
};

