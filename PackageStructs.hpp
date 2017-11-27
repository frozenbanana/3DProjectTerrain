#ifndef PACKAGESTRUCTS_H
#define PACKAGESTRUCTS_H

#include <GL/glew.h>

#include "PntLight.hpp"
#include "DirLight.hpp"
#include "SptLight.hpp"

//For Models

struct ModelData {
  std::vector<GLuint> s_VAOs;
  std::vector<std::vector<GLuint> > s_meshIndices;
  glm::mat4 s_modelMat;
};

/*ModelPack*/

//For Lights
struct LightPack {
  std::vector<PntLight> s_pnt_lights;
  std::vector<DirLight> s_dir_lights;
  std::vector<SptLight> s_spt_lights;
};

#endif
