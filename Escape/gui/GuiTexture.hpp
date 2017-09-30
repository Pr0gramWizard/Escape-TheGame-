#pragma once
#include <iostream>
#include <glfw3.h>
#include <glm.hpp>

class GuiTexture
{
public:
	GuiTexture(GLuint pTextureID, glm::vec2 pPosition, glm::vec2 pScale);
	~GuiTexture();

	// Getter
	GLuint getTextureID() const;
	glm::vec2 getPosition() const;
	glm::vec2 getScale() const;

	friend bool operator== (const GuiTexture &gui1, const GuiTexture &gui2);
	// Setter
	void setTextureID(GLuint pTextureID);
	void setPosition(glm::vec2 pPosition);
	void setScale(glm::vec2 pScale);

private:
	GLuint mTextureID;
	glm::vec2 mPosition;
	glm::vec2 mScale;
};

