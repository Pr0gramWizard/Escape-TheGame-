// Inclusion of the class declaration
#include "window.hpp"

// Default Constructor
Window::Window()
{
	// Checking if SDL was created successfully
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Log Message to console
		std::clog << "SDL could not be initilized! " << SDL_GetError() << std::endl;
		// Stopping the program
	}
	else
	{
		// Log Message to console
		std::clog << "SDL was initialized successfully!" << std::endl;
	}
}

// Create window
bool Window::createWindow(const char* pWindowTitle, unsigned int pWindowWidth, unsigned int pWindowHeight)
{
	// Creating the window

	// First we are setting up every important variable:
	// Title | Width | Height
	setWindowTitle(pWindowTitle);
	setWindowWidth(pWindowWidth);
	setWindowHeight(pWindowHeight);

	// Parameter: | Window Title | Initial x-Pos | Initial y-Pos | Window Width | Window Height | SDL Flags
	mWindow = SDL_CreateWindow(getWindowTitle(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, getWindowWidth(), getWindowHeight(), SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);

	// Checking if the window instance was created 
	if (mWindow == nullptr)
	{
		// Log message to console
		std::clog << "The window could not be created! " << SDL_GetError() << std::endl;
		// Stopping program
		return false;
	}
	else
	{
		// Log message to console
		std::clog << "The window was created successfully with:" << std::endl << "Title: " << getWindowTitle() << std::endl << "Width : " << getWindowWidth() << std::endl << "Height : " << getWindowHeight() << std::endl;
	}

	// Creating a new SDL GL Context variable
	SDL_GLContext glContext = SDL_GL_CreateContext(mWindow);

	// Checking if the variable was created successfully
	if (glContext == nullptr)
	{
		// Error message
		std::clog << "The SDL_GLContext variable could not be created! " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		// Success message
		std::clog << "The SDL_GLContext variable was created successfully" << std::endl;
	}

	if (glewInit() != 0)
	{
		std::clog << "GLEW could not be initiliazed! " << glGetError() << std::endl;
	}
	else
	{
		std::clog << "GLEW was initiliazed successfully" << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Everything worked fine
	return true;
}
// Returns the current Window Title
const char * Window::getWindowTitle() const
{
	return mWindowTitle;
}
// Returns the current Window Width
unsigned int Window::getWindowWidth() const
{
	return mWindowWidth;
}
// Returns the current Window Height
unsigned int Window::getWindowHeight() const
{
	return mWindowHeight;
}
// Returns the current Window instance
SDL_Window * Window::getWindow() const
{
	return mWindow;
}
// Sets the Window Title to a given parameter
void Window::setWindowTitle(const char * pWindowTitle)
{
	mWindowTitle = pWindowTitle;
}
// Sets the Window Width to a given parameter
void Window::setWindowWidth(unsigned int pWindowWidth)
{
	mWindowWidth = pWindowWidth;
}
// Sets the Window Height to a given parameter
void Window::setWindowHeight(unsigned int pWindowHeight)
{
	mWindowHeight = pWindowHeight;
}
// Changes the current window width/height
void Window::changeResolution(unsigned int pWindowWidth, unsigned int pWindowHeight)
{
	setWindowWidth(pWindowWidth);
	setWindowHeight(pWindowHeight);
	SDL_SetWindowSize(getWindow(), getWindowWidth(), getWindowHeight());

	SDL_Delay(7000);
}
// Default Destructor
Window::~Window()
{
}
