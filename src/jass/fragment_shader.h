#pragma once

#include "jass/shader.h"

class FragmentShader : public Shader {
public:
  FragmentShader(void);
  ~FragmentShader(void);

  void Create(void) override;
};
