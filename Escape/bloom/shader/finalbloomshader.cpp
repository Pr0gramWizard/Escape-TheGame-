#include "finalbloomshader.hpp"



// Constructor
FinalBloomShader::FinalBloomShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{

	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	this->getAllUniformLocations();
	this->bindAllAttributes();
	this->use();
	this->bindTextures();
	this->unuse();

	// Log Shader
	std::clog << "Bloom Shader class was created successfully!" << std::endl;
}

void FinalBloomShader::bindAllAttributes()
{
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "texCoord");
}


// Compilation of the vertex and fragment shader 
// Function: complieShader(Filepath, Filepath)
void FinalBloomShader::createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
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
		std::clog << "Bloom Vertex shader created successfully! " << std::endl;
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
		std::clog << "Bloom Fragment shader created successfully! " << std::endl;
	}

	// Compling both shader (using private class functions)
	compileVertexShader(pVertexShaderFilePath);
	compileFragementShader(pFragementShaderFilePath);
	linkShader();
	this->getAllUniformLocations();
	this->bindAllAttributes();
}

// Linking of vertex and fragment shader
void FinalBloomShader::linkShader()
{
	// First we create a new Program with the given Program ID
	setProgramID(glCreateProgram());

	std::cout << mProgramID << std::endl;

	// Then we attach both shader to the program
	glAttachShader(getProgramID(), getVertexShaderID());
	glAttachShader(getProgramID(), getFragementShaderID());

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
	// Delete:
	glDeleteShader(getVertexShaderID());
	glDeleteShader(getFragementShaderID());

}

// Tell the program to use the shader
void FinalBloomShader::use()
{
	// Starting the program with the shader together
	glUseProgram(getProgramID());
}

// Tell the program to stop using the shader
void FinalBloomShader::unuse()
{
	// Destroying refference to program
	glUseProgram(0);
}

// Reading fragment shader from file and compiling it
void FinalBloomShader::compileFragementShader(std::string pFragementShaderFilePath)
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

void FinalBloomShader::compileVertexShader(std::string pVertexShaderFilePath)
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
GLuint FinalBloomShader::getProgramID() const
{
	return mProgramID;
}
// Returns current Vertex Shader ID
GLuint FinalBloomShader::getVertexShaderID() const
{
	return mVertexShaderID;
}

// Returns current Fragement Shader ID
GLuint FinalBloomShader::getFragementShaderID() const
{
	return mFragementShaderID;
}
GLuint FinalBloomShader::getUniformLocation(const char* pUniformName)
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
void FinalBloomShader::setProgramID(int pProgramID)
{
	mProgramID = pProgramID;
}
// Sets current VertexShaderID to a given ID
void FinalBloomShader::setVertexShaderID(int pVertexShaderID)
{
	mVertexShaderID = pVertexShaderID;
}

// Sets current FragementShaderID to a given ID
void FinalBloomShader::setFragementShaderID(int pFragementShaderID)
{
	mFragementShaderID = pFragementShaderID;
}

void FinalBloomShader::loadInt(GLuint pLocation, GLuint pValue)
{
	glUniform1i(pLocation, pValue);
}

void FinalBloomShader::loadBool(GLuint pLocation, GLboolean pValue)
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

void FinalBloomShader::loadFloat(GLuint pLocation, GLfloat pValue)
{
	glUniform1f(pLocation, pValue);
}

void FinalBloomShader::bindTextures()
{
	this->loadInt(mLocation_scene, 0);
	this->loadInt(mLocation_bloomBlur, 1);
}

void FinalBloomShader::loadBloom(GLboolean pBloom)
{
	this->loadBool(mLocation_bloom, pBloom);
}

void FinalBloomShader::loadExposure(GLfloat pExposure)
{
	this->loadFloat(mLocation_exposure, pExposure);
}

// Destructor
FinalBloomShader::~FinalBloomShader()
{
	// Log Shader
	std::clog << "Bloom Shader class was destroyed successfully!" << std::endl;
}

void FinalBloomShader::getAllUniformLocations()
{
	mLocation_scene = glGetUniformLocation(getProgramID(), "scene");
	mLocation_bloomBlur = glGetUniformLocation(getProgramID(), "bloomBlur");
	mLocation_bloom = glGetUniformLocation(getProgramID(), "bloom");
	mLocation_exposure = glGetUniformLocation(getProgramID(), "exposure");
}

// Binding an attribtute to the shader
void FinalBloomShader::bindAttribute(GLuint pAttribute, const std::string & pAttributeName)
{
	// We bind the attribute to the given Program ID
	glBindAttribLocation(getProgramID(), pAttribute, pAttributeName.c_str());
	// Then we increase the number of attributes in the whole class
}
