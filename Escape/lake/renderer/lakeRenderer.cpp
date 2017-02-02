#include "lakeRenderer.hpp"

const char* LakeRenderer::DUDV_MAP = "lake/res/dudv.png";
const char* LakeRenderer::NORMAL_MAP = "lake/res/normal.png";
const float LakeRenderer::LAKE_WAVE_MOVEMENT_SPEED = 0.03f;

// constructor
LakeRenderer::LakeRenderer(LakeShader * pShader, glm::mat4 pProjectionMatrix, LakeFrameBuffers* pLakeFbos)
{
	mLakeFbos = pLakeFbos;
	mShader = pShader;
	mLakeMoveFactor = 0.0f;
	loadDuDvMap(DUDV_MAP);
	loadNormalMap(LakeRenderer::NORMAL_MAP);
	mShader->use();
	mShader->connectTextureUnits();
	mShader->loadProjectionMatrix(pProjectionMatrix);
	// use camera values instead!!
	mShader->loadNearFar(0.1f, 1000.0f);
	mShader->unuse();
}

// destructor
LakeRenderer::~LakeRenderer()
{
}

// renders a single Lake
void LakeRenderer::render(GLfloat pDeltaTime, glm::mat4 pViewMatrix, Lake &pLake, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE)
{
	this->startShader();
	this->loadViewMatrix(pViewMatrix);
	this->loadLights(pLights);
	this->loadFogData(0.01f, 2.0f);
	this->loadBackgroundColor(pRED, pGREEN, pBLUE);
	//update lake distortion
	mLakeMoveFactor += LakeRenderer::LAKE_WAVE_MOVEMENT_SPEED * pDeltaTime;
	if(mLakeMoveFactor >= 1.0f) {
		mLakeMoveFactor = 0.0f;
	}
	this->loadWaterMoveFactor(mLakeMoveFactor);
	prepareLake(&pLake);
	loadModelMatrix(&pLake);
	glDisable(GL_CULL_FACE);
	glDrawElements(GL_TRIANGLES, pLake.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	unbindLake();
	this->stopShader();
}


// binds the vertex array and the needed attributes for the Lake
void LakeRenderer::prepareLake(Lake pLake)
{
	Model* model = pLake.getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here

	// end texturepart
}

// binds the vertex array and the needed attributes for the Lake
void LakeRenderer::prepareLake(Lake* pLake)
{
	Model* model = pLake->getModel();
	glBindVertexArray(model->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Texturepart here
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mLakeFbos->getReflactionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mLakeFbos->getRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mLakeFbos->getRefractionDepthTexture());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->mDuDvMap);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, this->mNormalMap);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// end texturepart
}

// disables the vertex array and the used attibutes
void LakeRenderer::unbindLake()
{
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

// loads the model matrix for a Lake
void LakeRenderer::loadModelMatrix(Lake pLake)
{
	mShader->loadModelMatrix(pLake.getModelMatrix());
}

// loads the model matrix for a Lake
void LakeRenderer::loadModelMatrix(Lake* pLake)
{
	mShader->loadModelMatrix(pLake->getModelMatrix());
}

void LakeRenderer::loadViewMatrix(glm::mat4 pViewMatrix)
{
	mShader->loadViewMatrix(pViewMatrix);
}

void LakeRenderer::loadLights(vector<Light*> pLights)
{
	mShader->loadLights(pLights);
}

void LakeRenderer::loadFogData(GLfloat pDensity, GLfloat pGradient)
{
	mShader->loadFogData(pDensity, pGradient);
}

void LakeRenderer::loadBackgroundColor(GLfloat pRed, GLfloat pGreen, GLfloat pBlue)
{
	mShader->loadBackgroundColor(pRed, pGreen, pBlue);
}

void LakeRenderer::loadNearFar(GLfloat pNear, GLfloat pFar)
{
	mShader->loadNearFar(pNear, pFar);
}

void LakeRenderer::loadWaterMoveFactor(GLfloat pFactor) {
	mShader->loadWaterMoveFactor(pFactor);
}

void LakeRenderer::loadLakeSpotLightPosition(glm::vec3 pPos)
{
	this->mShader->loadLakeSpotLightPosition(pPos);
}

void LakeRenderer::loadLakeSpotLightColor(glm::vec3 pColor)
{
	this->mShader->loadLakeSpotLightColor(pColor);
}

void LakeRenderer::loadLakeSpotLightFactor(GLfloat pFactor)
{
	this->mShader->loadLakeSpotLightFactor(pFactor);
}

void LakeRenderer::loadLakeSpotLightTarget(glm::vec3 pTarget)
{
	this->mShader->loadLakeSpotLightTarget(pTarget);
}

void LakeRenderer::startShader()
{
	mShader->use();
}

void LakeRenderer::stopShader()
{
	mShader->unuse();
}

void LakeRenderer::loadDuDvMap(const char* pFile) {
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

void LakeRenderer::loadNormalMap(const char * pFile)
{
	glGenTextures(1, &mNormalMap);
	glBindTexture(GL_TEXTURE_2D, mNormalMap); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* normal = SOIL_load_image(pFile, &width, &height, 0, SOIL_LOAD_RGB);
	if (normal == 0)
	{
		std::cout << "The normal map texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, normal);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
	SOIL_free_image_data(normal);
	glBindTexture(GL_TEXTURE_2D, 0);
}

