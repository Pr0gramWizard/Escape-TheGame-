#pragma once

// renderer
#include "entityRenderer.hpp"
#include "terrainRenderer.hpp"

// entity
#include "entity.hpp"

// terrain
#include "terrain.hpp"

// shader
#include "entityshader.hpp"

// matrix
#include <mat4x4.hpp>

// list
#include <list>

class MainRenderer
{
public:
	// constructor
	MainRenderer(glm::mat4 pProjectionMatrix);
	// destructor
	~MainRenderer();

	// adds entities or terrains to render list
	void addToList(Entity &pEntity);
	void addToList(Terrain &pTerrain);
	void addToList(Entity &pEntity, RenderMode pMode);

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

private:
	EntityRenderer* mEntityRenderer;
	TerrainRenderer* mTerrainRenderer;

	list<Entity> mEntities;
	list<Terrain> mTerrains;
	list<Entity> mSpecialEntities;
};

