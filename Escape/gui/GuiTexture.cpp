#include "GuiTexture.hpp"


GuiTexture::GuiTexture(GLuint pTextureID, glm::vec2 pPosition, glm::vec2 pScale){
	mTextureID = pTextureID;
	mPosition = pPosition;
	mScale = pScale;
}

GuiTexture::~GuiTexture()
{
}

bool operator== (const GuiTexture &gui1, const GuiTexture &gui2)
{
	return (gui1.getTextureID() == gui2.getTextureID());
}

GLuint GuiTexture::getTextureID() const
{
	return mTextureID;
}

glm::vec2 GuiTexture::getPosition() const
{
	return mPosition;
}

glm::vec2 GuiTexture::getScale() const
{
	return mScale;
}

void GuiTexture::setTextureID(GLuint pTextureID){
	mTextureID = pTextureID;
}

void GuiTexture::setPosition(glm::vec2 pPosition){
	mPosition = pPosition;
}

void GuiTexture::setScale(glm::vec2 pScale){
	mScale = pScale;
}
