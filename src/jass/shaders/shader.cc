// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/shader.h"

namespace Shaders {

  Shader::Shader() {
    this->shader_id_ = 0;
  }

  void Shader::Create(const GLenum shader_type, const std::string &source) {
    GL_CHECK(this->shader_id_ = glCreateShader(shader_type));

    char const *source_str = source.c_str();
    GL_CHECK(glShaderSource(shader_id_, 1, &source_str, NULL));

    GL_CHECK(glCompileShader(shader_id_));

    GLint result = GL_FALSE;
    GL_CHECK(glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &result));

    if (result != GL_TRUE) {
      int log_length;

      GL_CHECK(glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &log_length));

      std::vector<char> error_message(log_length);

      GL_CHECK(glGetShaderInfoLog(shader_id_, log_length, NULL, &error_message[0]));

      fprintf(stdout, "%s\n", &error_message[0]);
    }
  }

  Shader::~Shader() {
    if (shader_id_) {
      GL_CHECK(glDeleteShader(shader_id_));
      this->shader_id_ = 0;
    }
  }

}  // namespace Shaders
