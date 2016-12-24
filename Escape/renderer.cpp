#include "renderer.hpp"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glClearColor(0.2f,0.3f,0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Model pModel,RenderMode pMode)
{
	glBindVertexArray(pModel.getVaoId());
	glEnableVertexAttribArray(0);
	switch (pMode)
	{
	case RenderMode::POINTS:
		glDrawElements(GL_POINTS, pModel.getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::LINES:
		glDrawElements(GL_LINES, pModel.getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::LINE_STRIP:
		glDrawElements(GL_LINE_STRIP, pModel.getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::LINE_LOOP:
		glDrawElements(GL_LINE_LOOP, pModel.getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::TRIANGLES:
		glDrawElements(GL_TRIANGLES, pModel.getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::TRIANGLE_STRIP:
		glDrawElements(GL_TRIANGLE_STRIP, pModel.getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	case RenderMode::TRIANGLE_FAN:
		glDrawElements(GL_TRIANGLE_FAN, pModel.getVerticesCount(), GL_UNSIGNED_INT, 0);
		break;
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::render(Model pModel)
{
	glBindVertexArray(pModel.getVaoId());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, pModel.getVerticesCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
