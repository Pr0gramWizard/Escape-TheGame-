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
		
		inputHandler();
		drawGame();
		SDL_GL_SwapWindow(mWindow->getWindow());
		
	}

}

void Game::drawGame()
{

	Vector3D cubePositions[] = {
		Vector3D(0.0f,  0.0f,  0.0f),
		Vector3D(2.0f,  5.0f, -15.0f),
		Vector3D(-1.5f, -2.2f, -2.5f),
		Vector3D(-3.8f, -2.0f, -12.3f),
		Vector3D(2.4f, -0.4f, -3.5f),
		Vector3D(-1.7f,  3.0f, -7.5f),
		Vector3D(1.3f, -2.0f, -2.5f),
		Vector3D(1.5f,  2.0f, -2.5f),
		Vector3D(1.5f,  0.2f, -1.5f),
		Vector3D(-1.3f,  1.0f, -1.5f)
	};

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// World space positions of our cubes


	GLuint VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	glClearDepth(1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glUseProgram(mShader->getProgramID());

	mShader->use();

	Matrix4D View(0.0f);

	View = View.Translation(Vector3D(0.0f, 0.0f, -3.0f));


	Matrix4D Projection(0.0f);

	Projection = Projection.Perspective(45.0f, (float)mWindow->getWindowWidth() / (float)mWindow->getWindowHeight(), 0.1f, 100.0f);


	GLint modelLoc = glGetUniformLocation(mShader->getProgramID(), "model");
	GLint viewLoc = glGetUniformLocation(mShader->getProgramID(), "view");
	GLint projLoc = glGetUniformLocation(mShader->getProgramID(), "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View.Elements[0]);
	// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Projection.Elements[0]);

	glBindVertexArray(VAO);

	static bool PrintModel;

	for (GLuint i = 0; i < 10; i++)
	{
		// Calculate the model matrix for each object and pass it to shader before drawing
		Matrix4D model;
		model.Translation(cubePositions[i]);
		GLfloat angle = 20.0f * i;
		model = model.Rotation(Vector3D(1.0f, 0.3f, 0.5f), angle);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model.Elements[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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
