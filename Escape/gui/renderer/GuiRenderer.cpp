#include "GuiRenderer.hpp"



GuiRenderer::GuiRenderer(Loader* pLoader, GuiShader* pShader){
	std::vector<float> quadPositions = { -0.5 , 0.5 , -0.5 , -0.5 , 0.5 , 0.5 , 0.5 ,-0.5 };
	mQuad = pLoader->loadDataToVao(quadPositions);
	mShader = pShader;
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(1920.0f), 0.0f, static_cast<GLfloat>(1080.0f));
	mShader->use();
	mShader->loadProjectionMatrix(projection);
}

void GuiRenderer::render() {
	mShader->use();
	glBindVertexArray(mQuad.getVaoId());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (unsigned int i = 0; i < mListOfGuiTextures.size(); ++i) {
		GuiTexture currentGUI = mListOfGuiTextures.at(i);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, currentGUI.getTextureID());
		glDrawArrays(GL_TRIANGLE_STRIP, 0, mQuad.getVerticesCount());
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	mShader->unuse();

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void GuiRenderer::addGUI(GuiTexture pGUI) {
	mListOfGuiTextures.push_back(pGUI);
}

void GuiRenderer::removeGUI(GuiTexture pGUI) {
	for (unsigned int i = 0; i < mListOfGuiTextures.size(); ++i) {
		if (mListOfGuiTextures.at(i) == pGUI) {
			mListOfGuiTextures.erase(mListOfGuiTextures.begin() + i);
		}
		else {
			std::cout << "This GUI is not in the list of all currently renderer GUIs!" << std::endl;
		}
	}
}

glm::mat4 GuiRenderer::getProjectionMatrix() const
{
	return mProjectionMatrix;
}


void GuiRenderer::setProjectionMatrix(glm::mat4 pProjectionMatrix){
	mProjectionMatrix = pProjectionMatrix;
}

GuiRenderer::~GuiRenderer()
{
}
