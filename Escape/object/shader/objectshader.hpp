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
// Light class
#include "../../light/light.hpp"

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

#define MAX_LIGHTS 4


// Defintion of the class Shader
class ObjectShader
{
	// All public member of the class 
public:
	// Constructor
	ObjectShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	// Compile Shader
	void createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	// Bind attribute
	void bindAttribute(GLuint pAttribute, const std::string & pAttributeName);
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
	void loadModelMatrix(glm::mat4 pMatrix);
	void loadProjectionMatrix(glm::mat4 pMatrix);
	void loadViewMatrix(glm::mat4 pMatrix);
	void loadLights(std::vector<Light*> pLights);
	void loadPlane(glm::vec4 pVector);
	void loadFogData(GLfloat pDensity, GLfloat pGradient);
	void loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue);

	// Destructor
	~ObjectShader();

	// All private member of the class
private:
	GLuint mProgramID;
	GLuint mVertexShaderID;
	GLuint mFragementShaderID;
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

private:
	void compileFragementShader(std::string pFragementShaderFilePath);
	void compileVertexShader(std::string pFragementShaderFilePath);
	void getAllUniformLocations();
	void loadMatrix(GLuint location, glm::mat4 pMatrix);
	void loadVector4f(GLuint pLocation, glm::vec4 pVector);
};

