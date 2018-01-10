#ifndef TEXTUREFUNCTIONS_H
#define TEXTUREFUNCTIONS_H

#include <GL/glew.h>

enum TextureEnums {
  POS_TEX,      //0
  NOR_TEX,      //1
  DIFFSPEC_TEX, //2
  LGTPOS_TEX,   //3
  SHADOW_TEX,    //4
  MESHDIFF_TEX, //5
  MESHSPEC_TEX, //6
  NORMAL_TEX,    //7
  COMPUTE_TEX,  //8
  NUM_OF_TEX
};

inline void Bind2DTextureTo(GLuint texture_id, TextureEnums target_unit) {
  glActiveTexture(GL_TEXTURE0 + target_unit);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}
#endif
