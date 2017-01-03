#include <iostream>
#include "game.hpp"




// The MAIN function, from here we start the application and run the game loop
int main()
{
	Game* Test = new Game(1270, 780, "Escape - The Game");

	Test->gameLoop();

	delete Test;
}
