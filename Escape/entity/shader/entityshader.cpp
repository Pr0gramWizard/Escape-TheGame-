// Inclusion of definiton of the class
#include "entityshader.hpp"


// Constructor
EntityShader::EntityShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{
	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	this->getAllUniformLocations();
	this->bindAllAttributes();

	// Log Shader
	std::clog << "Entity Shader class was created successfully!" << std::endl;
}

// Compilation of the vertex and fragment shader 
// Function: complieShader(Filepath, Filepath)
void EntityShader::createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
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

}

// Linking of vertex and fragment shader
void EntityShader::linkShader()
{
	// First we create a new Program with the given Program ID
	setProgramID(glCreateProgram());

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
void EntityShader::use()
{
	// Starting the program with the shader together
	glUseProgram(getProgramID());
}

// Tell the program to stop using the shader
void EntityShader::unuse()
{
	// Destroying refference to program
	glUseProgram(0);
}

// Reading fragment shader from file and compiling it
void EntityShader::compileFragementShader(std::string pFragementShaderFilePath)
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

void EntityShader::compileVertexShader(std::string pVertexShaderFilePath)
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

// Returns current Program ID
GLuint EntityShader::getProgramID() const
{
	return mProgramID;
}

// Returns current Vertex Shader ID
GLuint EntityShader::getVertexShaderID() const
{
	return mVertexShaderID;
}

// Returns current Fragement Shader ID
GLuint EntityShader::getFragementShaderID() const
{
	return mFragementShaderID;
}

// Returns the uniform location of given uniform
GLuint EntityShader::getUniformLocation(const char* pUniformName)
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

// Sets current Program ID to a given ID
void EntityShader::setProgramID(int pProgramID)
{
	mProgramID = pProgramID;
}

// Sets current VertexShaderID to a given ID
void EntityShader::setVertexShaderID(int pVertexShaderID)
{
	mVertexShaderID = pVertexShaderID;
}

// Sets current FragementShaderID to a given ID
void EntityShader::setFragementShaderID(int pFragementShaderID)
{
	mFragementShaderID = pFragementShaderID;
}

// Load float to given location
void EntityShader::loadFloat(GLuint pLocation, GLfloat pValue)
{
	glUniform1f(pLocation, pValue);
}

// Load vector (3x1) to given location
void EntityShader::loadVector(GLuint pLocation, glm::vec3 pVector)
{
	glUniform3f(pLocation, pVector.x, pVector.y, pVector.z);
}

// Load bool to given location
void EntityShader::loadBool(GLuint pLocation, GLboolean pValue)
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

// Load matrix (4x4) to given location
void EntityShader::loadMatrix(GLuint pLocation, glm::mat4 pMatrix)
{
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(pMatrix));
}

// Load vector (4x1) to given location
void EntityShader::loadVector4f(GLuint pLocation, glm::vec4 pVector)
{
	glUniform4f(pLocation, pVector.x, pVector.y, pVector.z, pVector.w);
}

// Load model matrix
void EntityShader::loadModelMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_modelMatrix, pMatrix);
}

// Load projection matrix
void EntityShader::loadProjectionMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_projectionMatrix, pMatrix);
}

// Load view matrix
void EntityShader::loadViewMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_viewMatrix, pMatrix);
}

// Load list of lights
void EntityShader::loadLights(std::vector<Light*> pLights, bool pDiscoTime)
{
	if (pDiscoTime) {
		for (unsigned int i = 0; i < MAX_LIGHTS; ++i) {
			if (i < pLights.size()) {
				loadVector(mLocation_lightPosition[i], pLights[i]->getPosition());
				loadVector(mLocation_lightColor[i], pLights[i]->getDiscoColor());
				loadVector(mLocation_lightAttenuation[i], pLights[i]->getDiscoAttenuation());
			}
			else {
				loadVector(mLocation_lightPosition[i], glm::vec3(0, 0, 0));
				loadVector(mLocation_lightColor[i], glm::vec3(0, 0, 0));
				loadVector(mLocation_lightAttenuation[i], glm::vec3(1, 0, 0));
			}
		}
	}
	else {
		for (unsigned int i = 0; i < MAX_LIGHTS; ++i) {
			if (i < pLights.size()) {
				loadVector(mLocation_lightPosition[i], pLights[i]->getPosition());
				loadVector(mLocation_lightColor[i], pLights[i]->getColor());
				loadVector(mLocation_lightAttenuation[i], pLights[i]->getAttenuation());
			}
			else {
				loadVector(mLocation_lightPosition[i], glm::vec3(0, 0, 0));
				loadVector(mLocation_lightColor[i], glm::vec3(0, 0, 0));
				loadVector(mLocation_lightAttenuation[i], glm::vec3(1, 0, 0));
			}
		}
	}
}

// Load clipping plane
void EntityShader::loadPlane(glm::vec4 pVector)
{
	this->loadVector4f(mLocation_plane, pVector);
}

// Log fog data
void EntityShader::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	this->loadFloat(mLocation_fogDensity, pDensity);
	this->loadFloat(mLocation_fogGradient, pGradient);
}

// Load Background color
void EntityShader::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	this->loadVector(mLocation_backgroundColor, glm::vec3(pRed, pGreen, pBlue));
}

// Destructor
EntityShader::~EntityShader()
{
	// Log Shader
	std::clog << "Entity Shader class was destroyed successfully!" << std::endl;
}

void EntityShader::getAllUniformLocations()
{
	// Caluclating every uniform location
	// Model matrix
	mLocation_modelMatrix = glGetUniformLocation(getProgramID(), "model");
	// Projection matrix
	mLocation_projectionMatrix = glGetUniformLocation(getProgramID(), "projection");
	// View matrix
	mLocation_viewMatrix = glGetUniformLocation(getProgramID(), "view");
	// Clipping plane
	mLocation_plane = glGetUniformLocation(getProgramID(), "plane");
	// Fog Density
	mLocation_fogDensity = glGetUniformLocation(getProgramID(), "fogDensity");
	// Fog Gradient
	mLocation_fogGradient = glGetUniformLocation(getProgramID(), "fogGradient");
	// Background Color
	mLocation_backgroundColor = glGetUniformLocation(getProgramID(), "backgroundColor");

	// Light locations
	const char* lightPos[] = {
		"lightPosition[0]",
		"lightPosition[1]",
		"lightPosition[2]",
		"lightPosition[3]",
		"lightPosition[4]",
		"lightPosition[5]"
	};

	const char* lightColor[] = {
		"lightColor[0]",
		"lightColor[1]",
		"lightColor[2]",
		"lightColor[3]",
		"lightColor[4]",
		"lightColor[5]"
	};

	const char* lightAttenuation[] = {
		"lightAttenuation[0]",
		"lightAttenuation[1]",
		"lightAttenuation[2]",
		"lightAttenuation[3]",
		"lightAttenuation[4]",
		"lightAttenuation[5]"
	};
	for (int i = 0; i < MAX_LIGHTS; ++i) {
		mLocation_lightPosition[i] = glGetUniformLocation(getProgramID(), lightPos[i]);
		mLocation_lightColor[i] = glGetUniformLocation(getProgramID(), lightColor[i]);
		mLocation_lightAttenuation[i] = glGetUniformLocation(getProgramID(), lightAttenuation[i]);
	}
}

// Binding an attribtute to the shader
void EntityShader::bindAttribute(GLuint pAttribute, const std::string & pAttributeName)
{
	// We bind the attribute to the given Program ID
	glBindAttribLocation(getProgramID(), pAttribute, pAttributeName.c_str());
	// Then we increase the number of attributes in the whole class
}

// Binding all important attributes for the entity
void EntityShader::bindAllAttributes()
{
	// Position vector
	this->bindAttribute(0, "position");
	// Normal vector
	this->bindAttribute(1, "normal");
	// Texture Corrdiantes
	this->bindAttribute(2, "texCoord");
}
