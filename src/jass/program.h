#pragma once

#include "jass/jass.h"

class Shader;

class Program {
public:
  Program(void);
  ~Program(void);

  void Create(std::shared_ptr<Shader> const &vertex_shader, std::shared_ptr<Shader> const &fragment_shader);

  GLuint program_id_;
};
