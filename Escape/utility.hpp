#pragma once
// This files contains every useful function that could be used cross-file

// Inclusion of the standard IO library
#include <iostream>

#include <SDL.h>
#include <glew.h>


// This function is used to log events/information to the console
void logMsg(const char* pMessage)
{
	std::clog << pMessage << std::endl;
}

void logErr(const char* pMessage, unsigned int pStatus)
{
	switch (pStatus)
	{
		case 0:
			std::cout << pMessage << ": " << SDL_GetError() << std::endl;
			break;
		case 1:
			std::cout << pMessage << ": " << glGetError() << std::endl;
		default:
			std::cout << "LogErr: " << "You choose a invalid status number!" << std::endl;
	}
}

// Converts degree to radian
inline float toRadians(float pAngle)
{
	float PI = 3.14159265358979323846f;
	return pAngle * (PI / 180.0f);
}




