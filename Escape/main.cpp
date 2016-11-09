#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <glut.h>



#include "game.hpp"

#include "vector3D.hpp"

int main(int args, char* argv[])
{

	Game* Escape;

	Escape = new Game();

	Escape->start();
	Escape->gameLoop();

	delete Escape;


	return 0;
}