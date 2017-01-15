#pragma once

// FreeType Library
#include <ft2build.h>
#include FT_FREETYPE_H

// OpenGLExtensionWrangler
#include <glew.h>

// OpenGLMath
#include <glm.hpp>
#include <vec2.hpp>

// Standarad I/0 Library
#include <iostream>

// Map
#include <map>

// Text Shader
#include "shader\textshader.hpp"

struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();

	void RenderText(TextShader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;
};

