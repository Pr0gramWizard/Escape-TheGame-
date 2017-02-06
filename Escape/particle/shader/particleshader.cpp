// Inclusion of definiton of the class
#include "particleshader.hpp"


// Constructor
ParticleShader::ParticleShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{

	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	this->getAllUniformLocations();
	this->bindAllAttributes();

	// Log Shader
	std::clog << "Particle Shader class was created successfully!" << std::endl;
}

ParticleShader::ParticleShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath, const std::string& pGeometryShaderFilePath)
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
	std::clog << "Particle Shader class was created successfully!" << std::endl;
}

void ParticleShader::bindAllAttributes()
{
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "normal");
	this->bindAttribute(2, "texCoord");
}


// Compilation of the vertex and fragment shader 
// Function: complieShader(Filepath, Filepath)
void ParticleShader::createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
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
void ParticleShader::linkShader()
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
void ParticleShader::use()
{
	// Starting the program with the shader together
	glUseProgram(getProgramID());
}

// Tell the program to stop using the shader
void ParticleShader::unuse()
{
	// Destroying refference to program
	glUseProgram(0);
}

// Reading fragment shader from file and compiling it
void ParticleShader::compileFragementShader(std::string pFragementShaderFilePath)
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

void ParticleShader::compileGeometryShader(std::string pGeometryShaderFilePath)
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

void ParticleShader::compileVertexShader(std::string pVertexShaderFilePath)
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
GLuint ParticleShader::getProgramID() const
{
	return mProgramID;
}
// Returns current Vertex Shader ID
GLuint ParticleShader::getVertexShaderID() const
{
	return mVertexShaderID;
}
GLuint ParticleShader::getGeometryShaderID() const
{
	return GLuint();
}
// Returns current Fragement Shader ID
GLuint ParticleShader::getFragementShaderID() const
{
	return mFragementShaderID;
}
GLuint ParticleShader::getUniformLocation(const char* pUniformName)
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

void ParticleShader::SetUniform(string sName, const float fValue)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform1fv(iLoc, 1, &fValue);
}

void ParticleShader::SetUniform(string sName, float* fValues, int iCount)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform1fv(iLoc, iCount, fValues);
}

// Setting vectors

void ParticleShader::SetUniform(string sName, glm::vec2* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform2fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ParticleShader::SetUniform(string sName, const glm::vec2 vVector)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform2fv(iLoc, 1, (GLfloat*)&vVector);
}

void ParticleShader::SetUniform(string sName, glm::vec3* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform3fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ParticleShader::SetUniform(string sName, const glm::vec3 vVector)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform3fv(iLoc, 1, (GLfloat*)&vVector);
}

void ParticleShader::SetUniform(string sName, glm::vec4* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform4fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ParticleShader::SetUniform(string sName, const glm::vec4 vVector)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform4fv(iLoc, 1, (GLfloat*)&vVector);
}

// Setting 3x3 matrices

void ParticleShader::SetUniform(string sName, glm::mat3* mMatrices, int iCount)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniformMatrix3fv(iLoc, iCount, GL_FALSE, (GLfloat*)mMatrices);
}

void ParticleShader::SetUniform(string sName, const glm::mat3 mMatrix)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniformMatrix3fv(iLoc, 1, GL_FALSE, (GLfloat*)&mMatrix);
}

// Setting 4x4 matrices

void ParticleShader::SetUniform(string sName, glm::mat4* mMatrices, int iCount)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniformMatrix4fv(iLoc, iCount, GL_FALSE, (GLfloat*)mMatrices);
}

void ParticleShader::SetUniform(string sName, const glm::mat4 mMatrix)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniformMatrix4fv(iLoc, 1, GL_FALSE, (GLfloat*)&mMatrix);
}

// Setting integers

void ParticleShader::SetUniform(string sName, int* iValues, int iCount)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform1iv(iLoc, iCount, iValues);
}

void ParticleShader::SetUniform(string sName, const int iValue)
{
	int iLoc = glGetUniformLocation(this->getProgramID(), sName.c_str());
	glUniform1i(iLoc, iValue);
}

void ParticleShader::SetModelAndNormalMatrix(string sModelMatrixName, string sNormalMatrixName, glm::mat4 mModelMatrix)
{
	SetUniform(sModelMatrixName, mModelMatrix);
	SetUniform(sNormalMatrixName, glm::transpose(glm::inverse(mModelMatrix)));
}

void ParticleShader::SetModelAndNormalMatrix(string sModelMatrixName, string sNormalMatrixName, glm::mat4* mModelMatrix)
{
	SetUniform(sModelMatrixName, mModelMatrix);
	SetUniform(sNormalMatrixName, glm::transpose(glm::inverse(*mModelMatrix)));
}

// Setter Functions
// Sets current Program ID to a given ID
void ParticleShader::setProgramID(int pProgramID)
{
	mProgramID = pProgramID;
}
// Sets current VertexShaderID to a given ID
void ParticleShader::setVertexShaderID(int pVertexShaderID)
{
	mVertexShaderID = pVertexShaderID;
}
void ParticleShader::setGeometryShaderID(int pGeometryShaderID)
{
}
// Sets current FragementShaderID to a given ID
void ParticleShader::setFragementShaderID(int pFragementShaderID)
{
	mFragementShaderID = pFragementShaderID;
}

void ParticleShader::loadFloat(GLuint pLocation, GLfloat pValue)
{
	glUniform1f(pLocation, pValue);
}

void ParticleShader::loadVector(GLuint pLocation, glm::vec3 pVector)
{
	glUniform3f(pLocation, pVector.x, pVector.y, pVector.z);
}

void ParticleShader::loadBool(GLuint pLocation, GLboolean pValue)
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

void ParticleShader::loadMatrix(GLuint pLocation, glm::mat4 pMatrix)
{
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(pMatrix));
}

void ParticleShader::loadVector4f(GLuint pLocation, glm::vec4 pVector)
{
	glUniform4f(pLocation, pVector.x, pVector.y, pVector.z, pVector.w);
}

void ParticleShader::loadModelMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_modelMatrix, pMatrix);
}

void ParticleShader::loadProjectionMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_projectionMatrix, pMatrix);
}

void ParticleShader::loadViewMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_viewMatrix, pMatrix);
}

void ParticleShader::loadLights(vector<Light*> pLights, bool pDiscoTime)
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

void ParticleShader::loadPlane(glm::vec4 pVector)
{
	this->loadVector4f(mLocation_plane, pVector);
}

void ParticleShader::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	this->loadFloat(mLocation_fogDensity, pDensity);
	this->loadFloat(mLocation_fogGradient, pGradient);
}

void ParticleShader::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	this->loadVector(mLocation_backgroundColor, glm::vec3(pRed, pGreen, pBlue));
}

void ParticleShader::loadPlayerBelowLake(GLfloat pPlayerBelowLake)
{
	this->loadBool(mLocation_playerBelowLake, pPlayerBelowLake);
}

// Destructor
ParticleShader::~ParticleShader()
{
	// Log Shader
	std::clog << "Shader class was destroyed successfully!" << std::endl;
}

void ParticleShader::getAllUniformLocations()
{
	mLocation_modelMatrix = glGetUniformLocation(getProgramID(), "model");
	mLocation_projectionMatrix = glGetUniformLocation(getProgramID(), "projection");
	mLocation_viewMatrix = glGetUniformLocation(getProgramID(), "view");
	mLocation_plane = glGetUniformLocation(getProgramID(), "plane");
	mLocation_fogDensity = glGetUniformLocation(getProgramID(), "fogDensity");
	mLocation_fogGradient = glGetUniformLocation(getProgramID(), "fogGradient");
	mLocation_backgroundColor = glGetUniformLocation(getProgramID(), "backgroundColor");
	mLocation_playerBelowLake = glGetUniformLocation(getProgramID(), "playerBelowLake");
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
void ParticleShader::bindAttribute(GLuint pAttribute, const std::string & pAttributeName)
{
	// We bind the attribute to the given Program ID
	glBindAttribLocation(getProgramID(), pAttribute, pAttributeName.c_str());
	// Then we increase the number of attributes in the whole class
}
