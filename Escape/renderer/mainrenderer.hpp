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

// skybox
#include "../skybox/skybox.hpp"
#include "../skybox/renderer/skyboxrenderer.hpp"
#include "../skybox/shader/skyboxshader.hpp"

// Text Rendering
#include "../text/TextRenderer.hpp"
#include "../text/shader/textshader.hpp"

// Object Rendering
#include "../object/object.hpp"
#include "../object/renderer/objectrenderer.hpp"
#include "../object/shader/objectshader.hpp"

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
	// destructor
	~MainRenderer();

	// adds entities or terrains to render list
	void addToList(Entity &pEntity);
	void addToList(Terrain &pTerrain);
	void addToList(Entity &pEntity, RenderMode pMode);
	void addToList(Skybox* Skybox);
	void addToList(Object& pObject);

	void setDrawMode(bool pMode);
	bool getDrawMode() const;

	void setNormalMode(bool pMode);
	bool getNormalMode() const;

	void setDebugMode(bool pMode);
	bool getDebugMode() const;

	// prepares for rendering
	void prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);
	// render
	void render(glm::mat4 pViewMatrix, float pPlayerBelowLake, vector<Light*> pLights, glm::vec4 pClipPlane, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);
	void renderDebugInformation();
	void clearLists();

	// Set FPS
	void setFPS(int pFPS);

	// cleans up when closing the game
	void cleanUp();

	EntityRenderer* mEntityRenderer;
	TerrainRenderer* mTerrainRenderer;
	TerrainRenderer* mNormalRenderer;
	SkyboxRenderer* mSkyboxRenderer;
	TextRenderer* mTextRenderer;
	ObjectRenderer* mObjectRenderer;

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
	Player* mPlayer;
	Skybox* mSkybox;

	list<Entity> mEntities;
	list<Entity> mSpecial;
	list<RenderMode> mRenderMode;
	list<Terrain> mTerrains;
	list<Object> mObjects;

	bool drawMode;
	bool debugMode;
	bool normalMode;

	int mFPS;
};

