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

	void setDrawMode(bool pMode);
	bool getDrawMode() const;

	// prepares for rendering
	void prepare(GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);
	// render
	void render(glm::mat4 pViewMatrix, vector<Light*> pLights, glm::vec4 pClipPlane, GLfloat pRED, GLfloat pGREEN, GLfloat pBLUE);
	// clears the render lists
	void clearLists();

	// cleans up when closing the game
	void cleanUp();

	EntityRenderer* mEntityRenderer;
	TerrainRenderer* mTerrainRenderer;
	SkyboxRenderer* mSkyboxRenderer;

public:
	static const char* ENTITY_VERTEX;
	static const char* ENTITY_FRAGMENT;
	static const char* TERRAIN_VERTEX;
	static const char* TERRAIN_FRAGMENT;
	static const char* SKYBOX_VERTEX;
	static const char* SKYBOX_FRAGMENT;

private:
	Player* mPlayer;
	Skybox* mSkybox;

	list<Entity> mEntities;
	list<Entity> mSpecial;
	list<RenderMode> mRenderMode;
	list<Terrain> mTerrains;

	bool drawMode;
};

