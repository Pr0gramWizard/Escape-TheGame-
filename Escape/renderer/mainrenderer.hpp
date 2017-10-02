#pragma once
// terrain
#include "../terrain/terrain.hpp"

#include "../terrain/shader/terrainShader.hpp"
#include "../terrain/renderer/terrainRenderer.hpp"
//lake
#include "../lake/lake.hpp"
#include "../lake/renderer/lakeRenderer.hpp"

// Text Rendering
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

// matrix
#include <mat4x4.hpp>

// list
#include <list>

class MainRenderer
{
public:
	// constructor
	MainRenderer(glm::mat4 pProjectionMatrix, Player* pPlayer);

	// adds entities or terrains to render list
	void addToList(Terrain &pTerrain);

	void setDrawMode(bool pMode);
	bool getDrawMode() const;

	void setNormalMode(bool pMode);
	bool getNormalMode() const;

	void setDebugMode(bool pMode);
	bool getDebugMode() const;

	// prepares for rendering
	void prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);
	// render
	void render(glm::mat4 pViewMatrix, vector<Light*> pLights, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, float pDelta);
	void renderDebugInformation();
	void clearLists();
	void clearTerrainList();

	// Set FPS
	void setFPS(int pFPS);



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
	// Terrain + Normal Vector
	TerrainRenderer* mNormalRenderer;
	// Text 
	TextRenderer* mTextRenderer;
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

	// List of all important stuff
	// Terrain
	list<Terrain> mTerrains;

	// Debug Modes
	bool drawMode;
	bool debugMode;
	bool normalMode;
	// FPS
	int mFPS;
};

