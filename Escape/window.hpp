#pragma once
// Inclusion of libraries

// SDL: SimpleDirectLayer 
// Used for creating and managing windows
#include <SDL.h>
// iostream: Input/Output-Stream
// Used for default input/output functions
#include <iostream>
// GLEW: OpenGL Extensions Wrangler Library
// Used for important OpenGL functions
#include <glew.h>

// Declaration of the window class
// This class controlls every window in the game
class Window
{
// All public functions
public:
	// Default constructor
	Window();
	// Creating window
	bool createWindow(const char* pWindowTitle, unsigned int pWindowWidth, unsigned int pWindowHeight );
	// Changes the window resolution
	void changeResolution(unsigned int pWindowWidth, unsigned int pWindowHeight);

	// Getter Functions
	const char* getWindowTitle() const;
	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;
	SDL_Window* getWindow() const;

	// Setter Functions
	void setWindowTitle(const char* pWindowTitle);
	void setWindowWidth(unsigned int pWindowWidth);
	void setWindowHeight(unsigned int pWindowHeight);

	// Default Destructor
	~Window();

// All private members
private:
	// Pointer to window instance
	SDL_Window* mWindow;
	// Window Title
	const char* mWindowTitle;
	// Window Width
	unsigned int mWindowWidth;
	// Window Height
	unsigned int mWindowHeight;


};

