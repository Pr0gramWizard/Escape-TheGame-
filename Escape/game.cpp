// Inclusion of the class declaration
#include "game.hpp"

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

GLfloat halfScreenWidth = 0;
GLfloat halfScreenHeight = 0;

// Default Constructor
Game::Game()
{
	mWindow = new Window();
	mEvent = new SDL_Event;
	mMainWorld = new World();
	// mCamera = new Camera();
	mShader = new Shader();
	setGameState(true);
	setFrameStartTime(0);
	setFrameCurrentTime(0);
	setFrameCount(0);
}
// Default destructor
Game::~Game()
{
	delete mWindow;
	delete mEvent;
	delete mMainWorld;
	delete mCamera;
}
// Start Function
void Game::start()
{
	mWindow->createWindow("Epic Dungeon Game", 800, 600);

	halfScreenWidth = (float) mWindow->getWindowWidth() / 2;
	halfScreenHeight = (float) mWindow->getWindowHeight() / 2;

	/*
	mShader->compileShader("shaders/colorShading.vert", "shaders/colorShading.frag");
	mShader->addAttribute("position");
	mShader->linkShader();
	*/

	glViewport((GLint) 0.0, (GLint) 0.0, (GLint) mWindow->getWindowWidth(), (GLint) mWindow->getWindowHeight()); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(0, mWindow->getWindowWidth(), 0, mWindow->getWindowHeight(), 0, 1000); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment



	

}

void Game::gameLoop()
{


	while (getGameState() != GameState::EXIT)
	{
		drawGame();
		inputHandler();
		SDL_GL_SwapWindow(mWindow->getWindow());
	}

}

void Game::drawGame()
{
	glEnable(GL_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT);

	// Render OpenGL here

	glPushMatrix();
	glTranslatef(halfScreenWidth, halfScreenHeight, -500);
	glRotatef(rotationX, 1, 0, 0);
	glRotatef(rotationY, 0, 1, 0);
	glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

	drawCube(halfScreenWidth, halfScreenHeight, -500, 200);

	glPopMatrix();


}

void Game::fpsCounter()
{
	setFrameStartTime(SDL_GetTicks());


	setFrameCount(getFrameCount() + 1);
	setFrameCurrentTime(SDL_GetTicks());

	if ((getFrameCurrentTime() - getFrameStartTime()) < (1000 / 60))
	{
		setFrameCount(0);
		SDL_Delay((1000 / 60) - (getFrameCurrentTime() - getFrameStartTime()));
	}

}

void Game::changeBackground(GLfloat pRed, GLfloat pGreen, GLfloat pBlue, GLfloat pAlpha)
{
	glClearDepth(1.0f);
	glClearColor(pRed, pGreen, pBlue, pAlpha);	
}

void Game::drawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
	GLfloat halfSideLength = edgeLength * 0.5f;

	GLfloat vertices[] =
	{
		// front face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// back face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

		// left face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// right face
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// top face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

		// top face
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
																																																																																																														   centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
	};

	 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// glColor3f(1.0f,0.0f,0.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
}

GameState Game::inputHandler()
{
		// Checks if there are any event to pull
		while (SDL_PollEvent(mEvent) != 0)
		{
			// If someone presses the X Button
			if (mEvent->type == SDL_QUIT)
			{
				// The game Status is set to FALSE ==> Game stops
				setGameState(false);
			}
			// Checks if someone pressed a button
			else if (mEvent->type == SDL_KEYDOWN)
			{

				const GLfloat rotationSpeed = 10;

				// Checks for a possible key
				switch (mEvent->key.keysym.sym)
				{
					// Case: ESC button
				case SDLK_ESCAPE:
					// The Game stops
					std::clog << "Exiting the game! " << std::endl;
					setGameState(false);
					break;
					// Case: Down button
				case SDLK_DOWN:
					// std::clog << "Press the DOWN key " << std::endl;
					rotationX += rotationSpeed;
					break;
					// Case: Up button
				case SDLK_UP:
					// std::clog << "Press the UP key " << std::endl;
					rotationX -= rotationSpeed;
					break;
					// Case: Left button
				case SDLK_LEFT:
					// std::clog << "Press the LEFT key " << std::endl;
					rotationY -= rotationSpeed;
					break;
					// Case: Right Button
				case SDLK_RIGHT:
					// std::clog << "Press the RIGHT key " << std::endl;
					rotationY += rotationSpeed;
					break;
					// Case: Space bar
				case SDLK_SPACE:
					std::clog << "Jump! " << std::endl;
					break;
					// Case: Default
				}
				return getGameState();
			}
			// Checks for mouse input
			else if (mEvent->type == SDL_MOUSEMOTION)
			{
				 // std::clog << mEvent->motion.x << " " << mEvent->motion.y << std::endl;
			}
			else if (mEvent->type == SDL_MOUSEMOTION)
			{
				if (mEvent->motion.x > 0 )
				{
					std::cout << "MOUSE : WHEEL DOWN" << std::endl;
				}
				else if (mEvent->wheel.x < 0)
				{
					std::cout << "MOUSE : WHEEL UP" << std::endl;
				}
			}
			return getGameState();
		}
}

GameState Game::getGameState() const
{
	return mGameState;
}

int Game::getFrameStartTime() const
{
	return mFrameStartTime;
}

int Game::getFrameCurrentTime() const
{
	return mFrameCurrentTime;
}

int Game::getFrameCount() const
{
	return mFrameCount;
}

void Game::setGameState(bool pGameState)
{
	if (pGameState)
	{
		mGameState = GameState::PLAY;
	}
	else
	{
		mGameState = GameState::EXIT;
	}
}

void Game::setFrameStartTime(int pFrameStartTime)
{
	mFrameStartTime = pFrameStartTime;
}

void Game::setFrameCurrentTime(int pFrameCurrentTime)
{
	mFrameCurrentTime = pFrameCurrentTime;
}

void Game::setFrameCount(int pFrameCount)
{
	mFrameCount = pFrameCount;
}

void Game::changeWindowSize(unsigned int pWindowWidth, unsigned int pWindowHeight)
{
	mWindow->changeResolution(pWindowWidth, pWindowHeight);
}
