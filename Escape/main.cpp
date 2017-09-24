#include <iostream>
#include "game/game.hpp"




// The MAIN function, from here we start the application and run the game loop
int main()
{
	Game* Test = new Game(1280, 720, "The Realm");

	Test->gameLoop();

	delete Test;
}
