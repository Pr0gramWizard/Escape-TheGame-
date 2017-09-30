#pragma once
#include <iostream>

// Loader class
#include "../../loader/loader.hpp"
// GUI Texture class
#include "../GuiTexture.hpp"
// GUI Shader
#include "../shader/GuiShader.hpp"


class GuiRenderer
{
public:
	GuiRenderer(Loader* pLoader,GuiShader* pShader);
	void render();

	void addGUI(GuiTexture pGUI);
	void removeGUI(GuiTexture pGUI);

	// Getter
	glm::mat4 getProjectionMatrix() const;

	// Setter
	void setProjectionMatrix(glm::mat4 pProjectionMatrix);
	~GuiRenderer();

private:
	Model mQuad;
	GuiShader* mShader;
	glm::mat4 mProjectionMatrix;
	std::vector<GuiTexture> mListOfGuiTextures;
};

