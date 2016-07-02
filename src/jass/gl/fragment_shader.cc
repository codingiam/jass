// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/gl/fragment_shader.h"

#include <string>

namespace GL {

FragmentShader::FragmentShader(boost::filesystem::path const &path) : Shader(path) {
}

FragmentShader::~FragmentShader() {
}

void FragmentShader::Create() {
  Shader::Create(GL_FRAGMENT_SHADER);
}

}  // namespace GL
