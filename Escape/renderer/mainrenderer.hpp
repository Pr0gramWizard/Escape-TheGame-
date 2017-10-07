#pragma once
// matrix
#include <mat4x4.hpp>
// list
#include <list>
// Terrain
#include "../terrain/terrain.hpp"
#include "../terrain/shader/terrainShader.hpp"
#include "../terrain/renderer/terrainRenderer.hpp"
// Lake
#include "../lake/lake.hpp"
#include "../lake/renderer/lakeRenderer.hpp"
// Text 
#include "../text/TextRenderer.hpp"
#include "../text/shader/textshader.hpp"
// Keyboard
#include "../input/keyboard.hpp"
// Player class
#include "../player/player.hpp"
// Skybox
#include "../skybox/Skybox.hpp"
#include "../skybox/shader/SkyboxShader.hpp"
// GUI
#include "../gui/GuiTexture.hpp"
#include "../gui/renderer/GuiRenderer.hpp"
#include "../gui/shader/GuiShader.hpp"
// Object
#include "../object/object.hpp"
#include "../object/renderer/objectrenderer.hpp"
#include "../object/shader/objectshader.hpp"
// Entity
#include "../entity/entity.hpp"
#include "../entity/renderer/entityRenderer.hpp"
#include "../entity/shader/entityshader.hpp"
// GLFW
#include <glfw3.h>

// Declaration of the Main Renderer class
class MainRenderer
{
public:
	// Constructor
	MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer, int pWidth, int pHeight);
	// Adds a terrain to the list
	void addToList(Terrain &pTerrain);
	void addToList(Skybox* pSkybox);
	void addToList(Object pObject);
	void addToList(std::unique_ptr<Entity>& pEntity);
	void addToList(std::unique_ptr<Cube>& pCube);

	// Setter
	void setDrawMode(bool pMode);

	// Getter
	bool getDrawMode() const;

	// Prepares the renderer
	void prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);

	// Render the scene
	void render(glm::mat4 pViewMatrix, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, float pDelta);

	// Render debug information
	void renderDebugInformation(int pWidth, int pHeight);

	// Set FPS
	void setFPS(int pFps);

	// Cleanup functions
	void clearLists();
	void clearTerrainList();
	void clearObjectList();
	void clearEntityList();

	// Resize function
	void resizeWindow(int pWidth, int pHeight);

// Public strings of the shader locations
public:
	static const char* TERRAIN_VERTEX;
	static const char* TERRAIN_FRAGMENT;
	static const char* SKYBOX_VERTEX;
	static const char* SKYBOX_FRAGMENT;
	static const char* GUI_VERTEX;
	static const char* GUI_FRAGMENT;
	static const char* TEXT_VERTEX;
	static const char* TEXT_FRAGMENT;
	static const char* OBJECT_VERTEX;
	static const char* OBJECT_FRAGMENT;
	static const char* ENTITY_VERTEX;
	static const char* ENTITY_FRAGMENT;

private:
	// Renderer
	// Terrain
	TerrainRenderer* mTerrainRenderer;
	// Skybox
	Skybox* mSkybox;
	// Skybox Shader
	SkyboxShader* mSkyboxShader;
	// GUI Renderer
	GuiRenderer* mGuiRenderer;
	// GUI Shader
	GuiShader* mGuiShader;
	// Pointer to Player
	Player* mPlayer;
	// Text Renderer
	TextRenderer* mTextRenderer;
	// Object Renderer
	ObjectRenderer* mObjectRenderer;
	// Entity Renderer
	EntityRenderer* mEntityRenderer;
	// List of all terrains
	std::vector<Terrain> mTerrains;
	// List of all objects
	std::vector<Object> mObjects;
	// List of all entites
	std::vector<std::unique_ptr<Entity> > mEntities;
	// List of all cubes
	std::vector<std::unique_ptr<Cube> > mCubes;
	// FPS
	int mFps;
	// Debug Modes
	bool drawMode;
	// Window Width
	int mWidth;
	// Window Height
	int mHeight;
};

