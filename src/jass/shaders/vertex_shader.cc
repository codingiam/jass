// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/vertex_shader.h"

#include <string>

namespace {
  std::string source =
    "#version 430 core"
    "\n"
    "layout(location = 0) in vec3 vpModelspace;"
    "layout(location = 1) in vec2 vUV;"
    "layout(location = 2) in vec3 vnModelspace;"
    ""
    "out vec2 UV;"
    "out vec3 Normal;"
    "out vec3 FragPos;"
    ""
    "uniform mat4 mvp;"
    "uniform mat4 model;"
    ""
    "uniform vec3 lightPos;"
    ""
    "void main() {"
    "  gl_Position = mvp * vec4(vpModelspace, 1.0f);"
    "  FragPos = vec3(model * vec4(vpModelspace, 1.0f));"
    "  Normal = Normal = mat3(transpose(inverse(model))) * vnModelspace;"
    "  UV = vUV;"
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
