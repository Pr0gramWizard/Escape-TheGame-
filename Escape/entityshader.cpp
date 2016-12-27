#include "entityshader.hpp"



EntityShader::EntityShader(const std::string& pVertexShaderFilePath, const std::string& pFragementShaderFilePath)
{
	this->createShader(pVertexShaderFilePath, pFragementShaderFilePath);
	std::cout << this->getProgramID() << std::endl;
}


EntityShader::~EntityShader()
{
}
