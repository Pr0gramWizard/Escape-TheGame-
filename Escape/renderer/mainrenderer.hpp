#pragma once

// renderer
#include "../entity/renderer/entityRenderer.hpp"
#include "../terrain/renderer/terrainRenderer.hpp"
#include "../lake/renderer/lakeRenderer.hpp"

// entity
#include "../entity/entity.hpp"

// terrain
#include "../terrain/terrain.hpp"

//lake
#include "../lake/lake.hpp"

// shader
#include "../entity/shader/entityShader.hpp"
#include "../terrain/shader/terrainShader.hpp"

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

	void setDrawMode(bool pMode);
	bool getDrawMode() const;

	// prepares for rendering
	void prepare();
	// render
	void render(glm::mat4 pViewMatrix, glm::vec4 pClipPlane);
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
	Player* mPlayer;

	list<Entity> mEntities;
	list<Entity> mSpecial;
	list<RenderMode> mRenderMode;
	list<Terrain> mTerrains;

	bool drawMode;
};

