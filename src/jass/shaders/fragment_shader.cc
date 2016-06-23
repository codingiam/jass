// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/fragment_shader.h"

#include <string>

namespace Shaders {

FragmentShader::FragmentShader() : Shader("data/shaders/default.frag") {
}

FragmentShader::~FragmentShader() {
}

void FragmentShader::Create() {
  Shader::Create(GL_FRAGMENT_SHADER);
}

}  // namespace Shaders
