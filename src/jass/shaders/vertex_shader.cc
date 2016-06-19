// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/vertex_shader.h"

#include <string>

namespace {
  std::string source =
    "#version 430 core"
    "\n"
    "layout(location = 0) in vec3 vp_modelspace;"
    "layout(location = 1) in vec2 texcoord;"
    ""
    "out vec2 Texcoord;"
    ""
    "uniform mat4 trans;"
    ""
    "void main() {"
    "  Texcoord = texcoord;"
    "  gl_Position = trans * vec4(vp_modelspace, 1.0);"
    "}";
}  // namespace

namespace Shaders {

VertexShader::VertexShader() : Shader() {
}

VertexShader::~VertexShader() {
}

void VertexShader::Create() {
  Shader::Create(GL_VERTEX_SHADER, source);
}

}  // namespace Shaders
