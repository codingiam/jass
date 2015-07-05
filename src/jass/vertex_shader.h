#pragma once

#include "jass/shader.h"

class VertexShader : public Shader {
public:
  VertexShader(void);
  ~VertexShader(void);

  void Create(void) override;
};
