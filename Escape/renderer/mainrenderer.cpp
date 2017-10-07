#include "mainrenderer.hpp"

// Shader locations
const char* MainRenderer::TERRAIN_VERTEX = "shaders/terrain.vert";
const char* MainRenderer::TERRAIN_FRAGMENT = "shaders/terrain.frag";
const char* MainRenderer::GUI_VERTEX = "shaders/gui.vert";
const char* MainRenderer::GUI_FRAGMENT = "shaders/gui.frag";
const char* MainRenderer::TEXT_VERTEX = "shaders/text.vert";
const char* MainRenderer::TEXT_FRAGMENT = "shaders/text.frag";
const char* MainRenderer::OBJECT_VERTEX = "shaders/object.vert";
const char* MainRenderer::OBJECT_FRAGMENT = "shaders/object.frag";
const char* MainRenderer::ENTITY_VERTEX = "shaders/entity.vert";
const char* MainRenderer::ENTITY_FRAGMENT = "shaders/entity.frag";


MainRenderer::MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer,int pWidth, int pHeight)
{
	// Creating terrain Shader
	TerrainShader* terrainshader = new TerrainShader(TERRAIN_VERTEX, TERRAIN_FRAGMENT);
	// Creating terrain renderer
	mTerrainRenderer = new TerrainRenderer(terrainshader, pProjectionMatrix);

	// Creating Text Shader
	TextShader* textshader = new TextShader(TEXT_VERTEX, TEXT_FRAGMENT);
	// Creating Text Renderer
	mTextRenderer = new TextRenderer(textshader, pWidth, pHeight);

	// Creating Object Shader
	ObjectShader* objectshader = new ObjectShader(OBJECT_VERTEX, OBJECT_FRAGMENT);
	// Creating Object Renderer
	mObjectRenderer= new ObjectRenderer(objectshader, pPlayer->getProjectionMatrix());

	// Creating Entity Shader
	EntityShader* entityShader = new EntityShader(ENTITY_VERTEX, ENTITY_FRAGMENT);
	// Creating Entity Renderer
	mEntityRenderer = new EntityRenderer(entityShader, pPlayer->getProjectionMatrix());

	// Setting draw mode to normal
	this->setDrawMode(0);

	// Setting player instance
	mPlayer = pPlayer;

	this->mWidth = pWidth;
	this->mHeight = pHeight;

}

void MainRenderer::resizeWindow(int pWidth, int pHeight) {
	this->mWidth = pWidth;
	this->mHeight = pHeight;
}

// Clearing whole screen with given color
void MainRenderer::prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE)
{
	glClearColor(pRED, pGREEN, pBLUE, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainRenderer::render(glm::mat4 pViewMatrix, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, float pDelta){

	// Preparing the scree
	this->prepare(pRED, pGREEN, pBLUE);

	mSkybox->render(pViewMatrix, mPlayer->getProjectionMatrix(),pDelta);

	// Polygon Mode
	if (this->getDrawMode())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	// Normal Mode
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (!mTerrains.empty()) {
		// Prepare terrain
		mTerrainRenderer->startShader();
		mTerrainRenderer->loadViewMatrix(pViewMatrix);
		mTerrainRenderer->loadLights(pLights, false);
		mTerrainRenderer->loadDepthCubemapTexture(pLights);
		mTerrainRenderer->loadPlayerBelowLake(false);
		mTerrainRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
		// Render Terrain
		for (Terrain &terrain : mTerrains)
		{
			mTerrainRenderer->loadTexture(terrain);
			mTerrainRenderer->render(terrain);
		}
		mTerrainRenderer->stopShader();
	}

	if (!mEntities.empty()) {
		mEntityRenderer->startShader();
		mEntityRenderer->loadViewMatrix(pViewMatrix);
		mEntityRenderer->loadLights(pLights, false);
		mEntityRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
		for (auto& data : mEntities) {
			data->increaseXRotation(1, pDelta);
			data->increaseYRotation(1, pDelta);
			data->increaseZRotation(1, pDelta);
			mEntityRenderer->render(data);
		}
		mEntityRenderer->stopShader();
	}

	if (!mCubes.empty()) {
		mEntityRenderer->startShader();
		mEntityRenderer->loadViewMatrix(pViewMatrix);
		mEntityRenderer->loadLights(pLights, false);
		mEntityRenderer->loadBackgroundColor(pRED, pGREEN, pBLUE);
		for (auto& data : mCubes) {
			mEntityRenderer->render(data);
		}
		mEntityRenderer->stopShader();
	}
	
	if (!mObjects.empty()) {
		// Prepare Objects
		mObjectRenderer->startShader();
		mObjectRenderer->loadViewMatrix(mPlayer->getViewMatrix());
		mObjectRenderer->loadLights(pLights, false);
		// Render objects
		for (Object object : mObjects) {
			mObjectRenderer->loadModelMatrix(&object);
			mObjectRenderer->render(object);
		}
		mObjectRenderer->stopShader();
	}

	this->renderDebugInformation(mWidth, mHeight);
}

void MainRenderer::setFPS(int pFps) {
	mFps = pFps;
}

// Render Debug information
void MainRenderer::renderDebugInformation(int pWidth, int pHeight)
{
	glEnable(GL_BLEND);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string PlayerPosition = "Player Position: ";

	float XPos = Math::round(mPlayer->getPosition().x, 2);
	float YPos = Math::round(mPlayer->getPosition().y, 2);
	float ZPos = Math::round(mPlayer->getPosition().z, 2);

	size_t characterStartPos = 0;
	size_t characterEndPos = 5;

	PlayerPosition =	PlayerPosition 
						+ std::to_string(XPos).substr(characterStartPos, characterEndPos) 
						+ "," + std::to_string(YPos).substr(characterStartPos, characterEndPos - 1) 
						+ "," + std::to_string(ZPos).substr(characterStartPos, characterEndPos);

	std::string FPS = "FPS: " + std::to_string(mFps);

	glm::vec3 fpsColor(1.0f,1.0f,1.0f);

	if (mFps < 60) {
		fpsColor = glm::vec3(0.8f, 0.0f, 0.0f);
	}
	else if (mFps < 120 && 60 < mFps) {
		fpsColor = glm::vec3(0.8f, 0.4f, 0.0f);
	}
	else if(mFps > 120){
		fpsColor = glm::vec3(0.0f, 0.8f, 0.0f);
	}

	mTextRenderer->RenderText(FPS.c_str(), 0.0f, mHeight - 20.0f, 0.5f, fpsColor);
	mTextRenderer->RenderText(PlayerPosition.c_str(), 0.0f, mHeight - 40.0f, 0.5f, glm::vec3(1, 1, 1));

}

void MainRenderer::addToList(Skybox* pSkybox) {
	mSkybox = pSkybox;
}

// Add terrain to the render list
void MainRenderer::addToList(Terrain &pTerrain){
	mTerrains.push_back(pTerrain);
}

// Add cube to the render list
void MainRenderer::addToList(std::unique_ptr<Cube>& pCube) {
	mCubes.push_back(std::move(pCube));
}

// Add terrain to the render list
void MainRenderer::addToList(Object pObject) {
	mObjects.push_back(pObject);
}

void MainRenderer::addToList(std::unique_ptr<Entity>& pEntity){
	mEntities.push_back(std::move(pEntity));
}

// Setting Draw Mode 
void MainRenderer::setDrawMode(bool pMode){
	drawMode = pMode;
}
// Returns the Draw Mode
bool MainRenderer::getDrawMode() const
{
	return drawMode;
}

// Clears the whole list
void MainRenderer::clearLists(){
	clearTerrainList();
	clearObjectList();
	clearEntityList();
}

// Clear the list of terrains
void MainRenderer::clearTerrainList(){
	mTerrains.clear();
}

void MainRenderer::clearObjectList(){
	mObjects.clear();
}

void MainRenderer::clearEntityList(){
	mEntities.clear();
}
