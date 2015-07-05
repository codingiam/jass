#pragma once

#include "jass/jass.h"

class Shader {
public:
  Shader(void);
  virtual ~Shader(void);

  virtual void Create() = 0;

public:
  GLuint shader_id_;
};
