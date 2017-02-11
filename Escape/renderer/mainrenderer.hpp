#pragma once

// entity
#include "../entity/entity.hpp"
#include "../entity/shader/entityShader.hpp"
#include "../entity/renderer/entityRenderer.hpp"
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

// Object Rendering
#include "../object/object.hpp"
#include "../object/renderer/objectrenderer.hpp"
#include "../object/shader/objectshader.hpp"

// Waterdrop Rendering
#include "../waterdrop/waterdrop.hpp"
#include "../waterdrop/renderer/waterdroprenderer.hpp"
#include "../waterdrop/shader/waterdropshader.hpp"

// Torch Rendering
#include "../torch/torch.hpp"
#include "../torch/renderer/torchrenderer.hpp"
#include "../torch/shader/torchshader.hpp"

// Keyboard
#include "../input/keyboard.hpp"

// Player class
#include "../player/player.hpp"

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
	void addToList(Entity &pEntity);
	void addToList(Terrain &pTerrain);
	void addToList(Entity &pEntity, RenderMode pMode);
	void addToList(Object& pObject);
	void addToList(Waterdrop& pWaterdrop);

	void setDrawMode(bool pMode);
	bool getDrawMode() const;

	void setNormalMode(bool pMode);
	bool getNormalMode() const;

	void setDebugMode(bool pMode);
	bool getDebugMode() const;

	// prepares for rendering
	void prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);
	// render
	void render(glm::mat4 pViewMatrix, float pPlayerBelowLake, vector<Light*> pLights, glm::vec4 pClipPlane, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE, bool pDiscoTime, float pFogDensity, float pFogGradient,float pDelta);
	void renderDebugInformation();
	void clearLists();

	// Set FPS
	void setFPS(int pFPS);



public:
	static const char* ENTITY_VERTEX;
	static const char* ENTITY_FRAGMENT;
	static const char* OBJECT_VERTEX;
	static const char* OBJECT_FRAGMENT;
	static const char* TERRAIN_VERTEX;
	static const char* TERRAIN_FRAGMENT;
	static const char* SKYBOX_VERTEX;
	static const char* SKYBOX_FRAGMENT;
	static const char* TEXT_VERTEX;
	static const char* TEXT_FRAGMENT;
	static const char* TERRAIN_NORMAL_VERTEX;
	static const char* TERRAIN_NORMAL_FRAGMENT;
	static const char* TERRAIN_NORMAL_GEOMETRY;

private:
	// Renderer
	// Entity
	EntityRenderer* mEntityRenderer;
	// Terrain
	TerrainRenderer* mTerrainRenderer;
	// Terrain + Normal Vector
	TerrainRenderer* mNormalRenderer;
	// Text 
	TextRenderer* mTextRenderer;
	// Object 
	ObjectRenderer* mObjectRenderer;
	// Waterdrop
	WaterdropRenderer* mWaterRenderer;
	// Torch
	TorchRenderer* mTorchRenderer;


	// Pointer to Player
	Player* mPlayer;

	// List of all important stuff
	// Entity
	list<Entity> mEntities;
	// Spectial Entity
	list<Entity> mSpecial;
	// Rendermodes
	list<RenderMode> mRenderMode;
	// Terrain
	list<Terrain> mTerrains;
	// Objects
	list<Object> mObjects;
	// Waterdrops
	list<Waterdrop> mWaterDrop;

	// Debug Modes
	bool drawMode;
	bool debugMode;
	bool normalMode;
	// FPS
	int mFPS;
};

