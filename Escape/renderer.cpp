#include "renderer.hpp"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::render(Model pModel)
{
	glBindVertexArray(pModel.getVaoId());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, pModel.getVerticesCount);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
