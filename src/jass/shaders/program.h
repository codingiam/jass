// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/jass.h"

namespace Shaders {

class VertexShader;
class FragmentShader;

class Program {
 public:
  Program(void);
  ~Program(void);

  void Create(std::shared_ptr<VertexShader> const &vertex_shader,
      std::shared_ptr<FragmentShader> const &fragment_shader);

  GLuint program_id_;
};

}  // namespace Shaders
