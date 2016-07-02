// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/gl/vertex_shader.h"

namespace GL {

VertexShader::VertexShader(boost::filesystem::path const &path) : Shader(path) {
}

VertexShader::~VertexShader() {
}

void VertexShader::Create() {
  Shader::Create(GL_VERTEX_SHADER);
}

}  // namespace GL
