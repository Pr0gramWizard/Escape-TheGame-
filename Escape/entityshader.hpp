#pragma once
#include "shader.hpp"
class EntityShader :
	public Shader
{
public:
	EntityShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath);
	~EntityShader();
	void addAttribute(const char* &pAttributeName);
};

