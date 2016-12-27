#pragma once

// renderer
#include "entityRenderer.hpp"
#include "terrainRenderer.hpp"

// entity
#include "entity.hpp"

// terrain
#include "terrain.hpp"

// shader
#include "testshader.hpp"

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
	void addToList(Entity pEntity);
	void addToList(Terrain pTerrain);

	// prepares for rendering
	void prepare();
	// render
	void render();
	// clears the render lists
	void clearLists();

	// cleans up when closing the game
	void cleanUp();

private:
	EntityRenderer* mEntityRenderer;
	TerrainRenderer* mTerrainRenderer;

	list<Entity> mEntities;
	list<Terrain> mTerrains;
};

