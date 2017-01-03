#pragma once

// renderer
#include "entityRenderer.hpp"
#include "terrainRenderer.hpp"
#include "lakeRenderer.hpp"

// entity
#include "entity.hpp"

// terrain
#include "terrain.hpp"

//lake
#include "lake\lake.hpp"

// shader
#include "entityshader.hpp"
#include "terrainshader.hpp"

// Keyboard
#include "keyboard.hpp"

// Player class
#include "player.hpp"

// Lake class
#include "lake\lake.hpp"

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
	void setLake(Lake *pLake);

	void setDrawMode(bool pMode);
	bool getDrawMode() const;

	// prepares for rendering
	void prepare();
	// render
	void render(glm::mat4 pViewMatrix);
	// clears the render lists
	void clearLists();

	// cleans up when closing the game
	void cleanUp();

public:
	static const char* ENTITY_VERTEX;
	static const char* ENTITY_FRAGMENT;
	static const char* TERRAIN_VERTEX;
	static const char* TERRAIN_FRAGMENT;
	static const char* LAKE_VERTEX;
	static const char* LAKE_FRAGMENT;

private:
	EntityRenderer* mEntityRenderer;
	TerrainRenderer* mTerrainRenderer;
	LakeRenderer* mLakeRenderer;
	Player* mPlayer;

	list<Entity> mEntities;
	list<Entity> mSpecial;
	list<RenderMode> mRenderMode;
	list<Terrain> mTerrains;
	Lake* mLake;

	bool drawMode;
};

