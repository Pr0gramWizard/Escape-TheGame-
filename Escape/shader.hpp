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

// Defintion of the class Shader
class Shader
{
	// All public member of the class 
public:
	// Constructor
	Shader();
	// Compile Shader
	void createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	// Add attribute
	virtual void addAttribute(const std::string& pAttributeName);
	// Linking Shader
	void linkShader();
	// Use/Unuse Function
	void use();
	void unuse();
	// Destructor
	~Shader();

protected:
	// Getter Functions
	int getNumberofAttributes() const;
	GLuint getProgramID() const;
	GLuint getVertexShaderID() const;
	GLuint getFragementShaderID() const;
	GLuint getUniformLocation(const char* pUniformName);

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
	GLuint mUniformLocation;
// All private functions of the class
private:
	void compileFragementShader(std::string pFragementShaderFilePath);
	void compileVertexShader(std::string pFragementShaderFilePath);
	// Increase/Decrease Functions
	void increaseNumberofAttributes();
	void decreaseNumberofAttributes();
};

