#pragma once
class Keyboard
{

public:

	static bool isKeyPressed(int key);

	static void setKeyPressed(int key, bool pressed);

private:
	static bool keys[1024];
};

