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
// GLFW
#include <glfw3.h>

// Declaration of the Main Renderer class
class MainRenderer
{
public:
	// Constructor
	MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer);
	// Adds a terrain to the list
	void addToList(Terrain &pTerrain);
	void addToList(Skybox* pSkybox);

	// Setter
	void setDrawMode(bool pMode);

	// Getter
	bool getDrawMode() const;

	// Prepares the renderer
	void prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);

	// Render the scene
	void render(glm::mat4 pViewMatrix, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, float pDelta);

	// Cleanup functions
	void clearLists();
	void clearTerrainList();

// Public strings of the shader locations
public:
	static const char* TERRAIN_VERTEX;
	static const char* TERRAIN_FRAGMENT;
	static const char* SKYBOX_VERTEX;
	static const char* SKYBOX_FRAGMENT;
	static const char* GUI_VERTEX;
	static const char* GUI_FRAGMENT;

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

	// List of all terrains
	list<Terrain> mTerrains;

	// Debug Modes
	bool drawMode;
};

