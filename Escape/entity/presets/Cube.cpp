#include "Cube.h"
// Defintion of all static variables for the cube class

// Cube Vertices
std::vector<float> Cube::sCubeVertices = {
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};
// Loader Object
std::unique_ptr<Loader> Cube::sLoader = std::make_unique <Loader>();

// Defaul constructor 
Cube::Cube() {
	// Set entity postion
	setPosition(glm::vec3(0.0f,0.0f,0.0f));
	// Set Entity rotation
	setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	// Set Entity scale
	setScale(1.0f);
	std::clog << "A cube without texture was created successfully!" << std::endl;
}

// Constructor for a textured cube with given properties
Cube::Cube(glm::vec3 pPosition, glm::vec3 pRotation, GLfloat pScale, std::string pCubeTexture){
	glGenVertexArrays(1, &mVaoId);
	glGenBuffers(1, &mVboId);
	glBindVertexArray(mVboId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, sCubeVertices.size() * sizeof(GLfloat), &sCubeVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
	this->loadTexture(pCubeTexture);
	// Set entity postion
	setPosition(pPosition);
	// Set Entity rotation
	setRotation(pRotation);
	// Set Entity scale
	setScale(pScale);
	// std::clog << "A textured cube was created successfully!" << std::endl;
}

// Constructor for a non-textured cube with given properties
Cube::Cube(glm::vec3 pPosition, glm::vec3 pRotation, GLfloat pScale) {
	// setModel(&(sLoader->loadDataToVao(sCubeVertices, sCubeTextureCoordinates, sCubeNormals, sCubeIndicies)));
	// Set entity postion
	setPosition(pPosition);
	// Set Entity rotation
	setRotation(pRotation);
	// Set Entity scale
	setScale(pScale);
	std::clog << "A textured cube was created successfully!" << std::endl;
}

// Constructor for a textured cube without properties
Cube::Cube(std::string pCubeTexture) {
	// setModel(&(sLoader->loadDataToVao(sCubeVertices, sCubeTextureCoordinates, sCubeNormals, sCubeIndicies, pCubeTexture.c_str())));
	// Set entity postion
	setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	// Set Entity rotation
	setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	// Set Entity scale
	setScale(1.0f);
	std::clog << "A textured cube was created successfully!" << std::endl;
}

// Default Destructor
Cube::~Cube(){
	std::clog << "The Cube instance was destroyed successfully!" << std::endl;
}

void Cube::loadTexture(std::string pCubeTexturePath) {
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* grass = SOIL_load_image(pCubeTexturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (grass == 0)
	{
		std::cout << "The cube texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(grass);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Cube::getVaoId() const{
	return mVaoId;
}

int Cube::getVerticesCount() const
{
	return mVertices;
}

int Cube::getTextureID() const
{
	return mTextureID;
}
