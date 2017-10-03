#include "SkyboxTexture.hpp"



SkyboxTexture::SkyboxTexture(std::string pFilePath){
	mFilePath = pFilePath;
	this->loadTexture();
}

void SkyboxTexture::loadTexture() {
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height;
		unsigned char* image;

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		for (GLuint i = 0; i < 6; i++)
		{
			std::string fielName = mDirections.at(i);
			std::string filePath = mFilePath + fielName + ".png";
			const char *finalFilePath = filePath.c_str();

			image = SOIL_load_image(finalFilePath, &width, &height, 0, SOIL_LOAD_RGB);
			if (image == 0)
			{
				std::cout << finalFilePath << " konnte nicht gefunden werden!" << std::endl;
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

		mTextureID = textureID;
}

std::string SkyboxTexture::getFilePath() const {
	return mFilePath;
}

GLuint SkyboxTexture::getTextureID() const {
	return mTextureID;
}

SkyboxTexture::~SkyboxTexture(){
	std::cout << "The texture of the skybox at " << this->getFilePath() << " was destroyed successfully!" << std::endl;
}
