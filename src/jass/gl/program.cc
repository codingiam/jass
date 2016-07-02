// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/gl/program.h"

#include <boost/format.hpp>

#include <vector>
#include <string>

#include "jass/gl/shader.h"
#include "jass/gl/vertex_shader.h"
#include "jass/gl/fragment_shader.h"

namespace GL {

Program::Program() {
  this->program_id_ = 0;
}

Program::~Program() {
  if (program_id_) {
    glDeleteProgram(program_id_);
    this->program_id_ = 0;
  }
}

void Program::Create(std::string const &vertex_shader_path,
    std::string const &fragment_shader_path) {
  auto vertex_shader =
      std::make_shared<VertexShader>(vertex_shader_path);
  vertex_shader->Create();

  auto fragment_shader =
      std::make_shared<FragmentShader>(fragment_shader_path);
  fragment_shader->Create();

  Create(vertex_shader, fragment_shader);
}

void Program::Create(std::shared_ptr<VertexShader> const &vertex_shader,
    std::shared_ptr<FragmentShader> const &fragment_shader) {
  this->program_id_ = glCreateProgram();

  glAttachShader(program_id_, vertex_shader->shader_id());
  glAttachShader(program_id_, fragment_shader->shader_id());

  glLinkProgram(program_id_);

  GLint result = GL_FALSE;
  glGetProgramiv(program_id_, GL_LINK_STATUS, &result);

  if (result != GL_TRUE) {
    GLint log_length;

    glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
      std::vector<char> error_message;

      error_message.reserve(static_cast<size_t>(log_length));

      glGetProgramInfoLog(program_id_, log_length, NULL,
          &error_message[0]);

      fprintf(stderr, "%s\n", &error_message[0]);
    }

    boost::format message = boost::format("Could not link program");
    throw std::runtime_error(message.str());
  }
}

}  // namespace GL
