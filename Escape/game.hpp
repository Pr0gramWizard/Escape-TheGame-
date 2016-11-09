#pragma once
// SDL: SimpleDirectLayer 
// Used for creating and managing windows and events
#include <SDL.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
// iostream: Input/Output-Stream
// Used for default input/output functions
#include <iostream>
// Window: Window class
// Used for managing windows created by the window class
#include "window.hpp"
// World: World class
// Used for creating and managing the game world
#include "world.hpp"
#include "camera.hpp"
#include "vector2D.hpp"
#include "vector3D.hpp"

// Different game states
enum class GameState { PLAY, EXIT };

// This class controls all the important game functions
class Game
{
// All public functions
public:
	// Default Constructor
	Game();
	// Default Destructor (probably not used)
	~Game();
	// Starting Function
	void start();
	// Changing the game window resolution
	void changeWindowSize(unsigned int pWindowWidth, unsigned int pWindowHeight);
	// Controlls the input by the user
	GameState inputHandler();
	// Main Game Loop
	void gameLoop();
	// Drawing Function
	void changeBackground(GLfloat pRed, GLfloat pGreen, GLfloat pBlue, GLfloat pAlpha);
	void drawGameField();
	// Getter Function
	GameState getGameState() const;
	int getFrameStartTime() const;
	int getFrameCurrentTime() const;
	int getFrameCount() const;
	GLdouble getFovy() const;
	GLdouble getAspect() const;
	GLdouble getZNear() const;
	GLdouble getZFar() const;

	// Setter Function
	void setGameState(bool pGameState);
	void setFrameStartTime(int pFrameStartTime);
	void setFrameCurrentTime(int pFrameCurrentTime);
	void setFrameCount(int pFrameCount);
	void setFovy(GLdouble);
	void setAspect(GLdouble);
	void setZNear(GLdouble);
	void setZFar(GLdouble);


// All private member
private:
	// Pointer to the window class
	Window* mWindow;
	// Pointer to the world class
	World* mMainWorld;
	// Pointer to Event instance
	SDL_Event* mEvent;
	// Pointer to the camera class
	Camera* mCamera;
	// Current Game State
	GameState mGameState;

// All Frame variables
private:
	int mFrameStartTime;
	int mFrameCurrentTime;
	int mFrameCount;

// All Camera variables
private:
	GLdouble mFovy;
	GLdouble mAspect;
	GLdouble mZNear;
	GLdouble mZFar;


// All private functions
private:
	void fpsCounter();

};

