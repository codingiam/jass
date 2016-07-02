// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GL_VERTEX_SHADER_H_
#define JASS_GL_VERTEX_SHADER_H_

#include <string>

#include "jass/gl/shader.h"

namespace GL {

class VertexShader : public Shader {
 public:
  explicit VertexShader(std::string const &path);
  ~VertexShader(void);

  void Create(void) override;
};

}  // namespace GL

#endif  // JASS_GL_VERTEX_SHADER_H_
