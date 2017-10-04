#pragma once

// FreeType Library
#include <ft2build.h>
#include FT_FREETYPE_H

// OpenGLExtensionWrangler
#include <glew.h>

// OpenGLMath
#include <glm.hpp>
#include <vec2.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>

// Standarad I/0 Library
#include <iostream>

// Map
#include <map>

// Text Shader
#include "shader\textshader.hpp"

// Struct that contains a single character
struct Character {
	// ID handle of the glyph texture
	GLuint TextureID;
	// Size of glyph
	glm::ivec2 Size;    
	// Offset from baseline to left/top of glyph
	glm::ivec2 Bearing;
	// Horizontal offset to advance to next glyph
	GLuint Advance;    
};

class TextRenderer
{
// Public functions
public:
	TextRenderer(TextShader* pShader, int pWidth, int pHeight);
	~TextRenderer();
	void prepareShader(int pWidth, int pHeight);
	void prepareText();
	void bindVAO();

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	GLuint getVAO() const;
	GLuint getVBO() const;
	

// Private members
private:
	std::map<GLchar, Character> Characters;
	GLuint mVAO, mVBO;
	TextShader* mShader;


};

