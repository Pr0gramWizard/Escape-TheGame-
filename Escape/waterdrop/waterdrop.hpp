#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes
#include <glew.h> // Contains all the necessery OpenGL includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SOIL.h>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include "../mesh/mesh.hpp"
#include "../math/math.hpp"

#include "shader\waterdropshader.hpp"



class Waterdrop
{
public:
	/*  Functions   */
	// Constructor, expects a filepath to a 3D Waterdrop.
	Waterdrop(GLchar* path, glm::vec3 pPosition,glm::vec3 pRotatio,GLfloat pScale, GLfloat pSpeed);

	// Draws the Waterdrop, and thus all its meshes
	void Draw(WaterdropShader* shader);

	void respawn();

	void updatePosition();

	void setAlive(bool pStatus);

	// Getter
	glm::vec3 getPosition();
	GLfloat getScale() const;
	glm::mat4 getModelMatrix();
	glm::vec3 getRotation() const;
	GLuint getTexture() const;
	// Setter
	void setPosition(glm::vec3 pPosition);
	void setScale(GLfloat pScale);
	void setRotation(glm::vec3 pRotation);

	void loadTexture(std::string pPath);


	bool mStatus;

private:

	/*  Waterdrop Data  */
	glm::vec3 mPosition;
	GLfloat mScale;
	GLfloat mSpeed;
	glm::vec3 mRotation;
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	GLuint mTexture;

	glm::vec3 mOutVector;

	glm::vec3 initialPosition;


	void loadWaterdrop(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

