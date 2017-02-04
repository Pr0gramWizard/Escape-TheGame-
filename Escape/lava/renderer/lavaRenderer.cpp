#include "lavaRenderer.hpp"

const char* LavaRenderer::DUDV_MAP = "Lava/res/dudv.png";
const char* LavaRenderer::LAVA_TEXTURE = "Lava/res/lava.png";
const float LavaRenderer::LAVA_WAVE_MOVEMENT_SPEED = 0.03f;

// constructor
LavaRenderer::LavaRenderer(LavaShader * pShader, glm::mat4 pProjectionMatrix)
{
	mShader = pShader;
	mLavaMoveFactor = 0.0f;
	loadDuDvMap(DUDV_MAP);
	loadLavaTexture(LavaRenderer::LAVA_TEXTURE);
	mShader->use();
	mShader->connectTextureUnits();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	// use camera values instead!!
	mShader->loadNearFar(0.1f, 1000.0f);
	mShader->unuse();
}

// destructor
LavaRenderer::~LavaRenderer()
{
}

// renders a single Lava
void LavaRenderer::render(GLfloat pDeltaTime, glm::mat4 pViewMatrix, Lava &pLava, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, bool pDiscoTime)
{
	this->startShader();
	this->loadViewMatrix(pViewMatrix);
	this->loadLights(pLights, pDiscoTime);
	this->loadFogData(0.01f, 2.0f);
	this->loadBackgroundColor(pRED, pGREEN, pBLUE);
	//update Lava distortion
	mLavaMoveFactor += LavaRenderer::LAVA_WAVE_MOVEMENT_SPEED * pDeltaTime;
	if(mLavaMoveFactor >= 1.0f) {
		mLavaMoveFactor = 0.0f;
	}
	this->loadLavaMoveFactor(mLavaMoveFactor);
	prepareLava(&pLava);
	loadModelMatrix(&pLava);
	glDrawElements(GL_TRIANGLES, pLava.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	unbindLava();
	this->stopShader();
}


// binds the vertex array and the needed attributes for the Lava
void LavaRenderer::prepareLava(Lava pLava)
{
	Model* model = pLava.getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here

	// end texturepart
}

// binds the vertex array and the needed attributes for the Lava
void LavaRenderer::prepareLava(Lava* pLava)
{
	Model* model = pLava->getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->mLavaTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->mDuDvMap);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// end texturepart
}

// disables the vertex array and the used attibutes
void LavaRenderer::unbindLava()
{
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

// loads the model matrix for a Lava
void LavaRenderer::loadModelMatrix(Lava pLava)
{
	mShader->loadModelMatrix(pLava.getModelMatrix());
}

// loads the model matrix for a Lava
void LavaRenderer::loadModelMatrix(Lava* pLava)
{
	mShader->loadModelMatrix(pLava->getModelMatrix());
}

void LavaRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void LavaRenderer::loadLights(vector<Light*> pLights, bool pDiscoTime)
{
	mShader->loadLights(pLights, pDiscoTime);
}

void LavaRenderer::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	mShader->loadFogData(pDensity, pGradient);
}

void LavaRenderer::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	mShader->loadBackgroundColor(pRed, pGreen, pBlue);
}

void LavaRenderer::loadNearFar(GLfloat pNear, GLfloat pFar)
{
	mShader->loadNearFar(pNear, pFar);
}

void LavaRenderer::loadLavaMoveFactor(GLfloat pFactor) {
	mShader->loadLavaMoveFactor(pFactor);
}

void LavaRenderer::startShader()
{
	mShader->use();
}

void LavaRenderer::stopShader()
{
	mShader->unuse();
}

void LavaRenderer::loadDuDvMap(const char* pFile) {
	glGenTextures(1, &mDuDvMap);
	glBindTexture(GL_TEXTURE_2D, mDuDvMap); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* dudv = SOIL_load_image(pFile, &width, &height, 0, SOIL_LOAD_RGB);
	if (dudv == 0)
	{
		std::cout << "The DuDv map texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dudv);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
	SOIL_free_image_data(dudv);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void LavaRenderer::loadLavaTexture(const char * pFile)
{
	glGenTextures(1, &mLavaTexture);
	glBindTexture(GL_TEXTURE_2D, mLavaTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* lava = SOIL_load_image(pFile, &width, &height, 0, SOIL_LOAD_RGB);
	if (lava == 0)
	{
		std::cout << "The lava texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, lava);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
	SOIL_free_image_data(lava);
	glBindTexture(GL_TEXTURE_2D, 0);
}

