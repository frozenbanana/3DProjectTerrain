#ifndef MESH_H
#define MESH_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Vertex.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>

struct Texture
{
  GLuint id;
  std::string type;
  aiString path;
};

class Mesh
{
private:
  GLuint m_vao, m_vbo, m_ebo;
  void SetupMesh();
public:
  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  std::vector<Texture> m_textures;

  Mesh();
  // Mesh(const Mesh& other);
  Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
  Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
  std::vector<glm::vec3> GetPos();
  GLuint GetVAO();
  GLuint GetVBO();
  GLuint GetEBO();
  void SetVAO(GLuint id);
  void SetVBO(GLuint id);
  void SetEBO(GLuint id);
  ~Mesh();
};

#endif
