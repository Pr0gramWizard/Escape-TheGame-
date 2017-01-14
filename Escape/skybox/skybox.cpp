#include "skybox.hpp"



Skybox::Skybox()
{
	mVertices = {
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

	mShader = new SkyboxShader("shaders/skybox.vert", "shaders/skybox.frag");

	this->loadVAO();



}

void Skybox::addTexture(const char * pTextureLocation)
{
	mFaces.push_back(pTextureLocation);
}

void Skybox::loadVAO()
{
	glGenVertexArrays(1, &mSkyBoxVAO);
	glGenBuffers(1, &mSkyBoxVBO);
	glBindVertexArray(mSkyBoxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mSkyBoxVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(GLfloat), &mVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	setVAO(mSkyBoxVAO);
	setVBO(mSkyBoxVBO);

}


void Skybox::setVAO(GLuint pVAO)
{
	this->mSkyBoxVAO = pVAO;
}

GLuint Skybox::getVAO() const
{
	return mSkyBoxVAO;
}

void Skybox::setVBO(GLuint pVBO)
{
	this->mSkyBoxVBO = pVBO;
}

GLuint Skybox::getVBO() const
{
	return mSkyBoxVBO;
}

void Skybox::setCubeMapTexture(GLuint pCubeMapTexture)
{
	mCubeMapTexture = pCubeMapTexture;
}

GLuint Skybox::getCubeMapTexture() const
{
	return mCubeMapTexture;
}

GLuint Skybox::loadTexture()
{
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height;
		unsigned char* image;

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		for (GLuint i = 0; i < mFaces.size(); i++)
		{
			image = SOIL_load_image(mFaces[i], &width, &height, 0, SOIL_LOAD_RGB);
			if (image == 0)
			{
				std::cout << mFaces[i] << " konnte nicht gefunden werden!" << std::endl;
			}
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return textureID;
}
