// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <GL/glew.h>

#include <memory>
#include <string>

namespace GL {

class VertexShader;
class FragmentShader;

class Program {
 public:
  Program(void);
  ~Program(void);

  void Create(std::string const &vertex_shader_path,
      std::string const &fragment_shader_path);

  GLuint program_id(void) {
    return this->program_id_;
  }

 private:
  void Create(std::shared_ptr<VertexShader> const &vertex_shader,
      std::shared_ptr<FragmentShader> const &fragment_shader);

  GLuint program_id_;
};

}  // namespace GL
