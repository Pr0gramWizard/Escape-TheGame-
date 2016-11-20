// Inclusion of the class declaration
#include "game.hpp"

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

	mShader->compileShader("shaders/colorShading.vert", "shaders/colorShading.frag");
	mShader->addAttribute("position");
	mShader->addAttribute("color");
	mShader->linkShader();
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
	glClearDepth(1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glUseProgram(mShader->getProgramID());

	mShader->use();

	glBegin(GL_TRIANGLES);

	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(-0.5f, 0.0f);

	glEnd();


	mShader->unuse();
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
					std::clog << "Press the DOWN key " << std::endl;
					break;
					// Case: Up button
				case SDLK_UP:
					std::clog << "Press the UP key " << std::endl;
					break;
					// Case: Left button
				case SDLK_LEFT:
					std::clog << "Press the LEFT key " << std::endl;
					break;
					// Case: Right Button
				case SDLK_RIGHT:
					std::clog << "Press the RIGHT key " << std::endl;
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
