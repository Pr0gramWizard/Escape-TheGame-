#include "Torch.hpp"



Torch::Torch(GLchar * path, glm::vec3 pPosition,glm::vec3 pRotation,GLfloat pScale)
{
	this->setPosition(pPosition);
	this->loadTorch(path);
	this->setScale(pScale);
	this->setRotation(pRotation);

	this->initialPosition = pPosition;

	this->mStatus = false;
}


void Torch::Draw(TorchShader* shader)
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
		this->meshes[i].Draw(shader);
}

glm::vec3 Torch::getPosition()
{
	return mPosition;
}

GLfloat Torch::getScale() const
{
	return mScale;
}

glm::vec3 Torch::getRotation() const
{
	return mRotation;
}

void Torch::setPosition(glm::vec3 pPosition)
{
	mPosition = pPosition;
}

void Torch::setScale(GLfloat pScale)
{
	mScale = pScale;
}


void Torch::setRotation(glm::vec3 pRotation)
{
	mRotation = pRotation;
}

GLuint Torch::getTexture() const
{
	return mTexture;
}

void Torch::loadTexture(std::string pPath)
{
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture Torch
											 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* grass = SOIL_load_image(pPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (grass == 0)
	{
		std::cout << "The Torch texture could not be found!" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(grass);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::mat4 Torch::getModelMatrix()
{
	return Math::getTransformationMatrix(this->getPosition(), this->getRotation().x, this->getRotation().y, this->getRotation().z, this->getScale());
}

void Torch::updatePosition()
{
	mOutVector.x = mPosition.x;
	mOutVector.y = mPosition.y;
	mOutVector.z = mPosition.z;
}

void Torch::respawn()
{
	mPosition.y = this->initialPosition.y;
}

void Torch::setAlive(bool pStatus)
{
	mStatus = pStatus;
}

void Torch::loadTorch(string path)
{
	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// Retrieve the directory path of the filepath
	this->directory = path.substr(0, path.find_last_of('/'));

	// Process ASSIMP's root node recursively
	this->processNode(scene->mRootNode, scene);
}

void Torch::processNode(aiNode * node, const aiScene * scene)
{
	// Process each mesh located at the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		// The node Torch only contains indices to index the actual Torchs in the scene. 
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}
	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}

}

Mesh Torch::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// Data to fill
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use Torchs where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	
	// Return a mesh Torch created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

vector<Texture> Torch::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;

	return textures;
}
