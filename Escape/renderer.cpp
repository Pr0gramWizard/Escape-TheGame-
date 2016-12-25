#include "renderer.hpp"

Renderer::Renderer()
{
	mShader = new Shader();
}

Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glClearColor(0.2f,0.3f,0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::addShader(const char* pVertexShader, const char* pFragmentShader)
{
	mShader->createShader(pVertexShader, pFragmentShader);
}

void Renderer::addUniformAttribute(glm::mat4 pMatrix, const char * pAttributeName)
{
	glm::mat4 view;
	view = pMatrix;
	mShader->addAttribute(pAttributeName);
	GLint viewLocation = mShader->getUniformLocation(pAttributeName);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
}



void Renderer::enableShader()
{
	mShader->use();
}

void Renderer::disableShader()
{
	mShader->unuse();
}

void Renderer::render(Entity pEntity,RenderMode pMode)
{
	glBindVertexArray(pEntity.getModel()->getVaoId());
	glEnableVertexAttribArray(0);
	switch (pMode)
	{
	case RenderMode::POINTS:
		glDrawElements(GL_POINTS, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::LINES:
		glDrawElements(GL_LINES, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::LINE_STRIP:
		glDrawElements(GL_LINE_STRIP, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::LINE_LOOP:
		glDrawElements(GL_LINE_LOOP, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::TRIANGLES:
		glDrawElements(GL_TRIANGLES, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::TRIANGLE_STRIP:
		glDrawElements(GL_TRIANGLE_STRIP, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::TRIANGLE_FAN:
		glDrawElements(GL_TRIANGLE_FAN, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::render(Entity pEntity)
{
	glBindVertexArray(pEntity.getModel()->getVaoId());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, pEntity.getModel()->getVerticesCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
