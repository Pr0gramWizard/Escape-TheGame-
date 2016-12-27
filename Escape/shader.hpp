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
// OpenGLMath
#include <gtc/type_ptr.hpp>
// 4x4 Matrix
#include <mat4x4.hpp>
// 3x1 Vector
#include <vec3.hpp>

// Defintion of the class Shader
class Shader
{
	// All public member of the class 
public:
	// Constructor
	Shader();
	// Compile Shader
	void createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	void bindAttribute(GLuint pAttribute, const std::string & pAttributeName);
	virtual void getAllUniformLocations();
	virtual void bindAllAttributes();
	// Linking Shader
	void linkShader();
	// Use/Unuse Function
	void use();
	void unuse();
	// Destructor
	~Shader();

	// Getter Functions
	int getNumberofAttributes() const;
	GLuint getProgramID() const;
	GLuint getVertexShaderID() const;
	GLuint getFragementShaderID() const;
	GLuint getUniformLocation(const char* pUniformName);

	// Loading uniform attributes into the shader
	void loadFloat(GLuint pLocation, GLfloat pValue);
	void loadVector(GLuint pLocation, glm::vec3 pVector);
	void loadBool(GLuint pLocation, GLboolean pValue);
	void loadMatrix(GLuint location, glm::mat4 pMatrix);

	// Setter Functions
	void setNumberofAttributes(int pAttribute);
	void setProgramID(int pProgramID);
	void setVertexShaderID(int pVertexShaderID);
	void setFragementShaderID(int pFragementShaderID);



// All private member of the class
private:
	int mNumberofAttributes;
	GLuint mProgramID;
	GLuint mVertexShaderID;
	GLuint mFragementShaderID;
// All private functions of the class
private:
	void compileFragementShader(std::string pFragementShaderFilePath);
	void compileVertexShader(std::string pFragementShaderFilePath);
	// Increase/Decrease Functions
	void increaseNumberofAttributes();
	void decreaseNumberofAttributes();
};

