// Inclusion of definiton of the class
#include "shadowshader.hpp"


// Constructor
ShadowShader::ShadowShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{

	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	this->getAllUniformLocations();
	this->bindAllAttributes();

	// Log Shader
	std::clog << "Shader class was created successfully!" << std::endl;
}

ShadowShader::ShadowShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath, const std::string& pGeometryShaderFilePath)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(pVertexShaderFilePath);
		fShaderFile.open(pFragementShaderFilePath);
		gShaderFile.open(pGeometryShaderFilePath);
		std::stringstream vShaderStream, fShaderStream, gShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		gShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		geometryCode = gShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();
	const GLchar * gShaderCode = geometryCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment, geometry;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// geometry shader
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gShaderCode, NULL);
	glCompileShader(geometry);
	// Print compile errors if any
	glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometry, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::geometry::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Shader Program
	this->mProgramID = glCreateProgram();
	glAttachShader(this->getProgramID(), vertex);
	glAttachShader(this->getProgramID(), fragment);
	glAttachShader(this->getProgramID(), geometry);
	glLinkProgram(this->getProgramID());
	// Print linking errors if any
	glGetProgramiv(this->getProgramID(), GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->getProgramID(), 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);

	this->getAllUniformLocations();
	this->bindAllAttributes();


	// Log Shader
	std::clog << "Shader class was created successfully!" << std::endl;
}

void ShadowShader::bindAllAttributes()
{
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "normal");
	this->bindAttribute(2, "texCoord");
}


// Compilation of the vertex and fragment shader 
// Function: complieShader(Filepath, Filepath)
void ShadowShader::createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{
	// First we create a VERTEX SHADER
	mVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	// Checking if the vertex shader was created successfully
	if (getVertexShaderID() == 0)
	{
		// Error message
		std::clog << "There was an error creating the vertex shader! " << glGetError() << std::endl;
	}
	else
	{
		// Success message
		std::clog << "Vertex shader created successfully! " << std::endl;
	}

	// Then we create a FRAGEMENT SHADER
	mFragementShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	// Checking if the fragement shader was created successfully
	if (getFragementShaderID() == 0)
	{
		// Error message
		std::clog << "There was an error creating the fragment shader! " << glGetError() << std::endl;
	}
	else
	{
		// Success message
		std::clog << "Fragment shader created successfully! " << std::endl;
	}

	// Compling both shader (using private class functions)
	compileVertexShader(pVertexShaderFilePath);
	compileFragementShader(pFragementShaderFilePath);
	linkShader();
	this->getAllUniformLocations();
	this->bindAllAttributes();
}

// Linking of vertex and fragment shader
void ShadowShader::linkShader()
{
	// First we create a new Program with the given Program ID
	setProgramID(glCreateProgram());

	// Then we attach both shader to the program
	glAttachShader(getProgramID(), getVertexShaderID());
	glAttachShader(getProgramID(), getFragementShaderID());
	glAttachShader(getProgramID(), getGeometryShaderID());

	// Link the Program together
	glLinkProgram(getProgramID());

	// Checking if the program was linked successfully
	GLint isLinked = 0;
	// Getting the status of the program
	glGetProgramiv(getProgramID(), GL_LINK_STATUS, (int*)&isLinked);
	// Checking the status
	if (isLinked == GL_FALSE)
	{
		// If it failed we need to know why
		GLint maxLength = 0;
		// Getting error message
		glGetProgramiv(getProgramID(), GL_INFO_LOG_LENGTH, &maxLength);
		// Saving error message in vector
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(getProgramID(), maxLength, &maxLength, &infoLog[0]);
		// Printing error message
		std::printf("%s\n", &(infoLog[0]));
		// Destroying every instance of the Program/Shader to clean up the rest
		glDeleteProgram(getProgramID());
		glDeleteShader(getVertexShaderID());
		glDeleteShader(getFragementShaderID());
	}

	// When the program works fine 
	// Detach/Delete every Shader
	// Detach:
	glDetachShader(getProgramID(), getVertexShaderID());
	glDetachShader(getProgramID(), getFragementShaderID());
	glDetachShader(getProgramID(), getGeometryShaderID());
	// Delete:
	glDeleteShader(getVertexShaderID());
	glDeleteShader(getFragementShaderID());
	glDeleteShader(getGeometryShaderID());

}

// Tell the program to use the shader
void ShadowShader::use()
{
	// Starting the program with the shader together
	glUseProgram(getProgramID());
}

// Tell the program to stop using the shader
void ShadowShader::unuse()
{
	// Destroying refference to program
	glUseProgram(0);
}

// Reading fragment shader from file and compiling it
void ShadowShader::compileFragementShader(std::string pFragementShaderFilePath)
{
	// Opening a file stream with the given file path
	std::ifstream fragementFile(pFragementShaderFilePath);
	// Checking if the file was opened correctly
	if (fragementFile.fail())
	{
		// Error message
		std::clog << "Failed to open: " << pFragementShaderFilePath.c_str() << std::endl;
	}
	else
	{
		// If file was opend correctly
		// We read the content of the file to a string to get our information

		// File content
		std::string fileContent = "";
		// Current line
		std::string line;

		// Itterating through the file until we reach the end of the file
		while (std::getline(fragementFile, line))
		{
			// Write everything into a string
			fileContent += line + "\n";
		}

		// Close file
		fragementFile.close();

		// Converting string to const char* to use a pointer
		const char* contentPtr = fileContent.c_str();

		// Loading the shader from the string
		glShaderSource(getFragementShaderID(), 1, &contentPtr, nullptr);
		// Compiling the shader
		glCompileShader(getFragementShaderID());

		// Checking if the shader was complied successfully
		GLint success = 0;
		// Getting info about the shader status
		glGetShaderiv(getFragementShaderID(), GL_COMPILE_STATUS, &success);
		// If the compilation failed
		if (success == GL_FALSE)
		{
			// Return an error message
			GLint maxLength = 0;
			glGetShaderiv(getFragementShaderID(), GL_INFO_LOG_LENGTH, &maxLength);
			// Save error message in vector of chars
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(getFragementShaderID(), maxLength, &maxLength, &errorLog[0]);
			// Print the error message
			std::printf("%s\n", &(errorLog[0]));
			// Delete shader to clean up
			glDeleteShader(getFragementShaderID());
		}
	}


}

void ShadowShader::compileGeometryShader(std::string pGeometryShaderFilePath)
{
	// Opening a file stream with the given file path
	std::ifstream geometryFile(pGeometryShaderFilePath);
	// Checking if the file was opened correctly
	if (geometryFile.fail())
	{
		// Error message
		std::clog << "Failed to open: " << pGeometryShaderFilePath.c_str() << std::endl;
	}
	else
	{
		// If file was opend correctly
		// We read the content of the file to a string to get our information

		// File content
		std::string fileContent = "";
		// Current line
		std::string line;

		// Itterating through the file until we reach the end of the file
		while (std::getline(geometryFile, line))
		{
			// Write everything into a string
			fileContent += line + "\n";
		}

		// Close file
		geometryFile.close();

		// Converting string to const char* to use a pointer
		const char* contentPtr = fileContent.c_str();

		// Loading the shader from the string
		glShaderSource(getGeometryShaderID(), 1, &contentPtr, nullptr);
		// Compiling the shader
		glCompileShader(getGeometryShaderID());

	}


}

void ShadowShader::compileVertexShader(std::string pVertexShaderFilePath)
{
	// Opening a file stream with the given file path
	std::ifstream vertexFile(pVertexShaderFilePath);
	// Checking if the file was opened correctly
	if (vertexFile.fail())
	{
		// Error message
		std::clog << "Failed to open: " << pVertexShaderFilePath.c_str() << std::endl;
	}
	else
	{
		// If file was opend correctly
		// We read the content of the file to a string to get our information

		// File content
		std::string fileContent = "";
		// Current line
		std::string line;

		// Itterating through the file until we reach the end of the file
		while (std::getline(vertexFile, line))
		{
			// Write everything into a string
			fileContent += line + "\n";
		}

		// Close file
		vertexFile.close();

		// Converting string to const char* to use a pointer
		const char* contentPtr = fileContent.c_str();

		// Loading the shader from the string
		glShaderSource(getVertexShaderID(), 1, &contentPtr, nullptr);
		// Compiling the shader
		glCompileShader(getVertexShaderID());

		// Checking if the shader was complied successfully
		GLint success = 0;
		// Getting info about the shader status
		glGetShaderiv(getVertexShaderID(), GL_COMPILE_STATUS, &success);
		// If the compilation failed
		if (success == GL_FALSE)
		{
			// Return an error message
			GLint maxLength = 0;
			glGetShaderiv(getVertexShaderID(), GL_INFO_LOG_LENGTH, &maxLength);
			// Save error message in vector of chars
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(getVertexShaderID(), maxLength, &maxLength, &errorLog[0]);
			// Print the error message
			std::printf("%s\n", &(errorLog[0]));
			// Delete shader to clean up
			glDeleteShader(getVertexShaderID());
		}
	}
}

// Getter Functions
// Returns current Program ID
GLuint ShadowShader::getProgramID() const
{
	return mProgramID;
}
// Returns current Vertex Shader ID
GLuint ShadowShader::getVertexShaderID() const
{
	return mVertexShaderID;
}
GLuint ShadowShader::getGeometryShaderID() const
{
	return GLuint();
}
// Returns current Fragement Shader ID
GLuint ShadowShader::getFragementShaderID() const
{
	return mFragementShaderID;
}
GLuint ShadowShader::getUniformLocation(const char* pUniformName)
{
	GLuint Location = glGetUniformLocation(this->getProgramID(), pUniformName);

	if (Location == GL_INVALID_INDEX)
	{
		std::clog << "There was an error finding: " << pUniformName << std::endl;
		return 0;
	}
	else
	{
		return Location;
	}
}

// Setter Functions
// Sets current Program ID to a given ID
void ShadowShader::setProgramID(int pProgramID)
{
	mProgramID = pProgramID;
}
// Sets current VertexShaderID to a given ID
void ShadowShader::setVertexShaderID(int pVertexShaderID)
{
	mVertexShaderID = pVertexShaderID;
}
void ShadowShader::setGeometryShaderID(int pGeometryShaderID)
{
}
// Sets current FragementShaderID to a given ID
void ShadowShader::setFragementShaderID(int pFragementShaderID)
{
	mFragementShaderID = pFragementShaderID;
}

void ShadowShader::loadFloat(GLuint pLocation, GLfloat pValue)
{
	glUniform1f(pLocation, pValue);
}

void ShadowShader::loadVector(GLuint pLocation, glm::vec3 pVector)
{
	glUniform3f(pLocation, pVector.x, pVector.y, pVector.z);
}

void ShadowShader::loadBool(GLuint pLocation, GLboolean pValue)
{
	if (pValue == 0)
	{
		glUniform1f(pLocation, 0);
	}
	else
	{
		glUniform1f(pLocation, 1);
	}
}

void ShadowShader::loadMatrix(GLuint pLocation, glm::mat4 pMatrix)
{
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(pMatrix));
}

void ShadowShader::loadVector4f(GLuint pLocation, glm::vec4 pVector)
{
	glUniform4f(pLocation, pVector.x, pVector.y, pVector.z, pVector.w);
}

void ShadowShader::loadModelMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_modelMatrix, pMatrix);
}

void ShadowShader::loadShadowMatrices(vector<glm::mat4> mShadowTransforms)
{
	for (int i = 0; i < 6; ++i) {
		loadMatrix(mLocation_shadowMatrices[i], mShadowTransforms[i]);
	}
}

void ShadowShader::loadFarplane(GLfloat pFar)
{
	loadFloat(mLocation_farplane, pFar);
}

// Destructor
ShadowShader::~ShadowShader()
{
	// Log Shader
	std::clog << "Shader class was destroyed successfully!" << std::endl;
}

void ShadowShader::getAllUniformLocations()
{
	GLuint mLocation_shadowMatrices[6];
	mLocation_modelMatrix = glGetUniformLocation(getProgramID(), "model");
	mLocation_lightPosition = glGetUniformLocation(getProgramID(), "lightPosition");
	mLocation_farplane = glGetUniformLocation(getProgramID(), "farplane");
	// Light locations
	const char* shadow[] = { 
		"shadowMatrices[0]", 
		"shadowMatrices[1]",
		"shadowMatrices[2]", 
		"shadowMatrices[3]", 
		"shadowMatrices[4]", 
		"shadowMatrices[5]" 
	};

	for (int i = 0; i < 6; ++i) {
		mLocation_shadowMatrices[i] = glGetUniformLocation(getProgramID(), shadow[i]);
	}
}

// Binding an attribtute to the shader
void ShadowShader::bindAttribute(GLuint pAttribute, const std::string & pAttributeName)
{
	// We bind the attribute to the given Program ID
	glBindAttribLocation(getProgramID(), pAttribute, pAttributeName.c_str());
	// Then we increase the number of attributes in the whole class
}
