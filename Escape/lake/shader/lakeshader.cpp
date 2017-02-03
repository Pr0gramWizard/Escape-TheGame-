// Inclusion of definiton of the class
#include "lakeshader.hpp"


// Constructor
LakeShader::LakeShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{
	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	this->getAllUniformLocations();
	this->bindAllAttributes();

	// Log Shader
	std::clog << "Shader class was created successfully!" << std::endl;
}

void LakeShader::bindAllAttributes()
{
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "normal");
	this->bindAttribute(2, "texCoord");
}


// Compilation of the vertex and fragment shader 
// Function: complieShader(Filepath, Filepath)
void LakeShader::createShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
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
void LakeShader::linkShader()
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
void LakeShader::use()
{
	// Starting the program with the shader together
	glUseProgram(getProgramID());
}

// Tell the program to stop using the shader
void LakeShader::unuse()
{
	// Destroying refference to program
	glUseProgram(0);
}

// Reading fragment shader from file and compiling it
void LakeShader::compileFragementShader(std::string pFragementShaderFilePath)
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

void LakeShader::compileVertexShader(std::string pVertexShaderFilePath)
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
GLuint LakeShader::getProgramID() const
{
	return mProgramID;
}
// Returns current Vertex Shader ID
GLuint LakeShader::getVertexShaderID() const
{
	return mVertexShaderID;
}
// Returns current Fragement Shader ID
GLuint LakeShader::getFragementShaderID() const
{
	return mFragementShaderID;
}
GLuint LakeShader::getUniformLocation(const char* pUniformName)
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
void LakeShader::setProgramID(int pProgramID)
{
	mProgramID = pProgramID;
}
// Sets current VertexShaderID to a given ID
void LakeShader::setVertexShaderID(int pVertexShaderID)
{
	mVertexShaderID = pVertexShaderID;
}
// Sets current FragementShaderID to a given ID
void LakeShader::setFragementShaderID(int pFragementShaderID)
{
	mFragementShaderID = pFragementShaderID;
}

void LakeShader::loadFloat(GLuint pLocation, GLfloat pValue)
{
	glUniform1f(pLocation, pValue);
}

void LakeShader::loadVector(GLuint pLocation, glm::vec3 pVector)
{
	glUniform3f(pLocation, pVector.x, pVector.y, pVector.z);
}

void LakeShader::loadBool(GLuint pLocation, GLboolean pValue)
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

void LakeShader::loadInt(GLuint pLocation, GLuint pValue)
{
	glUniform1i(pLocation, pValue);
}

void LakeShader::loadMatrix(GLuint pLocation, glm::mat4 pMatrix)
{
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(pMatrix));
}

void LakeShader::loadModelMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_modelMatrix, pMatrix);
}

void LakeShader::loadProjectionMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_projectionMatrix, pMatrix);
}

void LakeShader::loadViewMatrix(glm::mat4 pMatrix)
{
	loadMatrix(mLocation_viewMatrix, pMatrix);
}

void LakeShader::loadLights(vector<Light*> pLights, bool pDiscoTime)
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

void LakeShader::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	this->loadFloat(mLocation_fogDensity, pDensity);
	this->loadFloat(mLocation_fogGradient, pGradient);
}

void LakeShader::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	this->loadVector(mLocation_backgroundColor, glm::vec3(pRed, pGreen, pBlue));
}

void LakeShader::loadNearFar(GLfloat pNear, GLfloat pFar)
{
	this->loadFloat(mLocation_near, pNear);
	this->loadFloat(mLocation_far, pFar);
}

void LakeShader::loadLakeSpotLightPosition(glm::vec3 pPos)
{
	this->loadVector(mLocation_lakeSpotLightPosition, pPos);
}

void LakeShader::loadLakeSpotLightColor(glm::vec3 pColor)
{
	this->loadVector(mLocation_lakeSpotLightColor, pColor);
}

void LakeShader::loadLakeSpotLightFactor(GLfloat pFactor)
{
	this->loadFloat(mLocation_lakeSpotLightFactor, pFactor);
}

void LakeShader::loadLakeSpotLightTarget(glm::vec3 pTarget)
{
	this->loadVector(mLocation_lakeSpotLightTarget, pTarget);
}

void LakeShader::loadWaterMoveFactor(GLfloat pFactor) {
	this->loadFloat(mLocation_waterMoveFactor, pFactor);
}

void LakeShader::connectTextureUnits()
{
	this->loadInt(mLocation_reflectionTexture, 0);
	this->loadInt(mLocation_refractionTexture, 1);
	this->loadInt(mLocation_depthMap, 2);
	this->loadInt(mLocation_dudvMap, 3);
	this->loadInt(mLocation_normalMap, 4);
}

// Destructor
LakeShader::~LakeShader()
{
	// Log Shader
	std::clog << "Shader class was destroyed successfully!" << std::endl;
}

void LakeShader::getAllUniformLocations()
{
	mLocation_modelMatrix = glGetUniformLocation(getProgramID(), "model");
	mLocation_projectionMatrix = glGetUniformLocation(getProgramID(), "projection");
	mLocation_viewMatrix = glGetUniformLocation(getProgramID(), "view");
	mLocation_reflectionTexture = glGetUniformLocation(getProgramID(), "reflectionTexture");
	mLocation_refractionTexture = glGetUniformLocation(getProgramID(), "refractionTexture");
	mLocation_depthMap = glGetUniformLocation(getProgramID(), "depthMap");
	mLocation_fogDensity = glGetUniformLocation(getProgramID(), "fogDensity");
	mLocation_fogGradient = glGetUniformLocation(getProgramID(), "fogGradient");
	mLocation_backgroundColor = glGetUniformLocation(getProgramID(), "backgroundColor");
	mLocation_near = glGetUniformLocation(getProgramID(), "near");
    mLocation_far = glGetUniformLocation(getProgramID(), "far");
	mLocation_dudvMap = glGetUniformLocation(getProgramID(), "dudvMap");
	mLocation_waterMoveFactor = glGetUniformLocation(getProgramID(), "waterMoveFactor");
	mLocation_normalMap = glGetUniformLocation(getProgramID(), "normalMap");
	mLocation_lakeSpotLightPosition = glGetUniformLocation(getProgramID(), "lakeSpotLightPosition");
	mLocation_lakeSpotLightColor = glGetUniformLocation(getProgramID(), "lakeSpotLightColor");
	mLocation_lakeSpotLightTarget = glGetUniformLocation(getProgramID(), "lakeSpotLightTarget");;
	mLocation_lakeSpotLightFactor = glGetUniformLocation(getProgramID(), "lakeSpotLightFactor");;
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
void LakeShader::bindAttribute(GLuint pAttribute, const std::string & pAttributeName)
{
	// We bind the attribute to the given Program ID
	glBindAttribLocation(getProgramID(), pAttribute, pAttributeName.c_str());
	// Then we increase the number of attributes in the whole class
}
