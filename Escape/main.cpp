#include <iostream>
#include "game.hpp"




// The MAIN function, from here we start the application and run the game loop
int main()
{
	Game* Test = new Game(2500, 1200, "Beten wir dass das Game funktioniert!");

	Test->gameLoop();
}
