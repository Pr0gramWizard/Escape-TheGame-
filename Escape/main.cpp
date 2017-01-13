#include <iostream>
#include "game/game.hpp"




// The MAIN function, from here we start the application and run the game loop
int main()
{
	Game* Test = new Game(800, 600, "Escape - The Game");

	Test->gameLoop();

	delete Test;
}
