// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/vertex_shader.h"

#include <string>

namespace Shaders {

VertexShader::VertexShader() : Shader("data/shaders/default.vert") {
}

VertexShader::~VertexShader() {
}

void VertexShader::Create() {
  Shader::Create(GL_VERTEX_SHADER);
}

}  // namespace Shaders
