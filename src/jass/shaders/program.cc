// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/program.h"

#include <algorithm>

#include "jass/shaders/vertex_shader.h"
#include "jass/shaders/fragment_shader.h"

namespace Shaders {

Program::Program() {
  this->program_id_ = 0;
}

Program::~Program() {
  if (program_id_) {
    GL_CHECK(glDeleteProgram(program_id_));
    this->program_id_ = 0;
  }
}

void Program::Create(std::shared_ptr<VertexShader> const &vertex_shader,
    std::shared_ptr<FragmentShader> const &fragment_shader) {
  GL_CHECK(this->program_id_ = glCreateProgram());

  GL_CHECK(glAttachShader(program_id_, vertex_shader->shader_id()));
  GL_CHECK(glAttachShader(program_id_, fragment_shader->shader_id()));

  GL_CHECK(glLinkProgram(program_id_));

  GLint Result = GL_FALSE;
  GL_CHECK(glGetProgramiv(program_id_, GL_LINK_STATUS, &Result));

  if (Result != GL_TRUE) {
    int InfoLogLength;
    GL_CHECK(glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &InfoLogLength));

    std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, static_cast<int>(1)));

    GL_CHECK(glGetProgramInfoLog(program_id_, InfoLogLength, NULL, &ProgramErrorMessage[0]));
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
  }
}

}  // namespace Shaders
