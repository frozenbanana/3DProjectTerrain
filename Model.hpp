#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Transform.hpp"
#include "Mesh.hpp"
#include "GLOBALS.hpp"
#include "PackageStructs.hpp"

class Model : public Transform
{
private:
  std::vector<Mesh> m_meshes;
  std::string m_directory;
  Transform m_transform;
  std::vector<Texture> m_textures_loaded;
  std::vector<GLuint> m_vaos;
  std::vector<GLuint> m_vbos;
  std::vector<GLuint> m_ebos;
  void ProcessNode(aiNode* node, const aiScene* scene);
  Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
  GLint TextureFromFile(const char* path, std::string directory, std::string typeName);
  std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
  std::vector<GLuint> GetVAOs();
  std::vector<GLuint> GetVBOs();
  std::vector<GLuint> GetEBOs();
  std::vector<std::vector<GLuint> > GetModelMeshesIndices();
  std::vector<std::vector<glm::vec3> > GetModelMeshesPos();
  std::vector< std::vector<Texture> > GetMeshTextures();
  ModelData m_modelData;
  GLfloat m_minX, m_maxX;
  GLfloat m_minY, m_maxY;
  GLfloat m_minZ, m_maxZ;
  void ControllMinMaxPos(glm::vec3 meshPos);
public:
  Model();
  Model(std::string path);
  void LoadModel(std::string path);
  // void SetTexture(std::string path, std::string typeName);
  std::vector<Mesh> GetModelMeshes();
  ModelData& GetModelData();
  ~Model();
};

#endif
