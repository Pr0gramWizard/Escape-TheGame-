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

GLint TextureFromFile(const char* path, string directory);

class Object
{
public:
	/*  Functions   */
	// Constructor, expects a filepath to a 3D Object.
	Object(GLchar* path);

	// Draws the Object, and thus all its meshes
	void Draw(ObjectShader* shader);

	// Getter
	glm::vec3 getPosition() const;

	// Setter
	void setPosition(glm::vec3 pPosition);

	glm::mat4 getModelMatrix() const;

private:
	/*  Object Data  */
	glm::vec3 mPosition;
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

										/*  Functions   */
										// Loads a Object with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadObject(string path);

	// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

GLint TextureFromFile(const char* path, string directory);