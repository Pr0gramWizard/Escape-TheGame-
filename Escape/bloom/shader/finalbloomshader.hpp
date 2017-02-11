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
// glm::value_prt
#include <gtc/type_ptr.hpp>

using namespace std;
// Defintion of the class Shader
class FinalBloomShader
{
	// All public member of the class 
public:
	// Constructor
	FinalBloomShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
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
	GLuint getFragementShaderID() const;
	GLuint getUniformLocation(const char* pUniformName);

	// Setter Functions
	void setProgramID(int pProgramID);
	void setVertexShaderID(int pVertexShaderID);
	void setFragementShaderID(int pFragementShaderID);

	void bindTextures();

	// load uniform variables
	void loadBloom(GLboolean pBloom);
	void loadExposure(GLfloat pExposure);
	void loadIsBurning(GLboolean pIsBurning);
	void loadGamma(GLfloat pGamma);

	// Destructor
	~FinalBloomShader();

	// All private member of the class
private:
	GLuint mProgramID;
	GLuint mVertexShaderID;
	GLuint mFragementShaderID;
	// All private functions of the class

	//uniform locations
	GLuint mLocation_gamma;
	GLuint mLocation_scene;
	GLuint mLocation_bloomBlur;
	GLuint mLocation_bloom;
	GLuint mLocation_exposure;
	GLuint mLocation_burning;
	GLuint mLocation_isBurning;

private:
	void compileFragementShader(std::string pFragementShaderFilePath);
	void compileVertexShader(std::string pFragementShaderFilePath);
	void getAllUniformLocations();
	void bindAllAttributes();
	void loadInt(GLuint pLocation, GLuint pValue);
	void loadBool(GLuint pLocation, GLboolean pValue);
	void loadFloat(GLuint pLocation, GLfloat pValue);
};