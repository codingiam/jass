// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/fragment_shader.h"

#include <string>

namespace {
  std::string source =
    "#version 430 core"
    "\n"
    "in vec2 Texcoord;"
    ""
    "out vec4 color;"
    ""
    "uniform sampler2D tex;"
    "uniform vec4 theColor;"
    ""
    "void main()"
    "{"
    "  color = texture(tex, Texcoord) * theColor;"
    "}";
}  // namespace

namespace Shaders {

FragmentShader::FragmentShader() {
}

FragmentShader::~FragmentShader() {
}

void FragmentShader::Create() {
  Shader::Create(GL_FRAGMENT_SHADER, source);
}

}  // namespace Shaders
