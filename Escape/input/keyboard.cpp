#include "keyboard.hpp"

bool Keyboard::keys[1024] = { false };

bool Keyboard::isKeyPressed(int key) {
	return (key >= 0 && key < 1024) ? Keyboard::keys[key] : false;
}

void Keyboard::setKeyPressed(int key, bool pressed)
{
	if (key >= 0 && key < 1024)
	{
		Keyboard::keys[key] = pressed;
	}
}
