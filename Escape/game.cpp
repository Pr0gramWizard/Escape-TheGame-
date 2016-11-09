// Inclusion of the class declaration
#include "game.hpp"

// Default Constructor
Game::Game()
{
	mWindow = new Window();
	mEvent = new SDL_Event;
	mMainWorld = new World(5);
	mCamera = new Camera();
	setGameState(true);
	setFrameStartTime(0);
	setFrameCurrentTime(0);
	setFrameCount(0);
	setFovy(0);
	setAspect(0);
	setZNear(0);
	setZFar(0);
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
	mWindow->createWindow("Ina kann nicht lesen", 800, 600);

	glViewport(0, 0, mWindow->getWindowWidth(), mWindow->getWindowHeight());

	glEnable(GL_DEPTH_TEST);

}

void Game::gameLoop()
{

	/*
		float CubeVertices[108] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	*/

	mMainWorld->init(mWindow->getWindowWidth(), mWindow->getWindowHeight());
	

	while (getGameState() != GameState::EXIT)
	{
		fpsCounter();
		SDL_GL_SwapWindow(mWindow->getWindow());
		inputHandler();

		Matrix4D View;

		View = mCamera->GetViewMatrix();

		gluPerspective(mCamera->getZoom(), (GLfloat)mWindow->getWindowWidth() / (GLfloat)mWindow->getWindowHeight(), 0.1f, 100.0f);
	}

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

void Game::drawGameField()
{
	/*
	GLfloat TriangleA[6] = { 0.0f, 0.5f,0.0f, 0.0f,-0.5f, 0.0f };
	GLfloat TriangleB[6] = { 0.0f, 0.5f,0.5f, 0.0f,0.0f, 0.0f };
	GLfloat TriangleC[6] = { 0.0f, 0.0f,0.5f, 0.0f,0.0f, -0.5f };
	GLfloat TriangleD[6] = { 0.0f, 0.0f,0.0f, -0.5f,-0.5f, 0.0f };
	GLfloat ColorA[9] = { 1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f };
	GLfloat ColorB[9] = { 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f };
	GLfloat ColorC[9] = { 0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f };
	GLfloat ColorD[9] = { 0.0f,1.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f };

	GLfloat MainTriangle[6] = { 0.0f, 0.5f,0.5f,0.0f,-0.5f,0.0f };
	GLfloat MainColor[9] = { 1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f };

	GLfloat TopLeftQuad[8] = {-1.0f, 1.0f, -0.75f,1.0f,-0.75f,0.75f,-1.0f,0.75f};
	GLfloat TopRightQuad[8] = { 1.0f, 1.0f, 0.75f,1.0f,0.75f,0.75f,1.0f,0.75f };
	GLfloat DownLeftQuad[8] = { -1.0f, -1.0f, -0.75f,-1.0f,-0.75f,-0.75f,-1.0f,-0.75f };
	GLfloat DownRightQuad[8] = { 1.0f, -1.0f, 0.75f,-1.0f,0.75f,-0.75f,1.0f,-0.75f };
	GLfloat MainColorQ[12] = { 1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f };
	


	mMainWorld->addTriangle(TriangleA, ColorA);
	mMainWorld->addTriangle(TriangleB, ColorB);
	mMainWorld->addTriangle(TriangleC, ColorC);
	mMainWorld->addTriangle(TriangleD, ColorD);



	mMainWorld->addTriangle(MainTriangle, MainColor);
	mMainWorld->addQuad(TopLeftQuad, MainColorQ);
	mMainWorld->addQuad(TopRightQuad, MainColorQ);
	mMainWorld->addQuad(DownLeftQuad, MainColorQ);
	mMainWorld->addQuad(DownRightQuad, MainColorQ);

	std::cout << mMainWorld->getNumberOfElements() << std::endl;
	std::cout << mMainWorld->getMaxNumberOfElements() << std::endl;
	*/


	Vector2D FirstVertex(0.0f, 0.5f);
	Vector2D SecondVertex(0.5f, 0.0f);
	Vector2D ThirdVertex(-0.5f, 0.0f);

	mMainWorld->addTriangle(FirstVertex, SecondVertex, ThirdVertex);

	/*
	Vector2D A(-0.5f, 0.0f);
	Vector2D B(-1.5f, 1.0f);
	Vector2D C(0.5f, 1.0f);

	FirstVertex + A;
	SecondVertex + B;
	ThirdVertex + C;


	mMainWorld->addTriangle(FirstVertex, ThirdVertex, SecondVertex);

	Vector2D D(1.0f, 0.0f);
	Vector2D E(1.0f, 0.0f);
	Vector2D F(1.0f, 0.0f);

	FirstVertex + D;
	SecondVertex + E;
	ThirdVertex + F;

	mMainWorld->addTriangle(FirstVertex, SecondVertex, ThirdVertex);

	Vector2D NewA(0.0f, -0.5f);
	Vector2D NewB(-0.5f, 0.0f);
	Vector2D NewC(0.5f, 0.0f);

	mMainWorld->addTriangle(NewA, NewC, NewB);

	Vector2D nA(-0.5f, 0.0f);
	Vector2D nB(-0.5f, -1.0f);
	Vector2D nC(-0.5f, -1.0f);

	NewA + nA;
	NewB + nB;
	NewC + nC;
	
	mMainWorld->addTriangle(NewA, NewC, NewB);

	Vector2D nD(1.0f, 0.0f);
	Vector2D nE(1.0f, 0.0f);
	Vector2D nF(1.0f, 0.0f);

	NewA + nD;
	NewB + nE;
	NewC + nF;

	mMainWorld->addTriangle(NewA, NewB, NewC);
	*/


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
					setFovy(getFovy() - 5.0);
					break;
					// Case: Up button
				case SDLK_UP:
					std::clog << "Press the UP key " << std::endl;
					setFovy(getFovy() + 5.0);
					break;
					// Case: Left button
				case SDLK_LEFT:
					std::clog << getZFar() << std::endl;
					setZFar(getZFar() + 10.0);
					break;
					// Case: Right Button
				case SDLK_RIGHT:
					std::clog << getZFar() << std::endl;
					setZFar(getZFar() - 10.0);
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

GLdouble Game::getFovy() const
{
	return mFovy;
}

GLdouble Game::getAspect() const
{
	return mAspect;
}

GLdouble Game::getZNear() const
{
	return mZNear;
}

GLdouble Game::getZFar() const
{
	return mZFar;
}

void Game::setFovy(GLdouble pFovy)
{
	mFovy = pFovy;
}

void Game::setAspect(GLdouble pAspect)
{
	mAspect = pAspect;
}

void Game::setZNear(GLdouble pZNear)
{
	mZNear = pZNear;
}

void Game::setZFar(GLdouble pZFar)
{
	mZFar = pZFar;
}
