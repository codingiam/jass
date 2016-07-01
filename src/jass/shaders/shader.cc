// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/shader.h"

#include <fstream>
#include <iterator>

namespace Shaders {

  Shader::Shader(std::string const &path) {
    this->path_ = path;
    this->shader_id_ = 0;
  }

  void Shader::Create(const GLenum shader_type) {
    GL_CHECK(this->shader_id_ = glCreateShader(shader_type));

    const std::string source = LoadSource();

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

      fprintf(stderr, "%s\n", &error_message[0]);

      boost::format message =
        boost::format("Could not compile shader: %s") % path_;
      throw std::runtime_error(message.str());
    }
  }

  std::string Shader::LoadSource() {
    std::ifstream data_source { path_, std::ifstream::in };
    if (!data_source.is_open()) {
      boost::format message =
        boost::format("Could not load shader: %s") % path_;
      throw std::runtime_error(message.str());
    }
    std::string source { std::istreambuf_iterator<char>(data_source), std::istreambuf_iterator<char>() };
    return source;
  }

  Shader::~Shader() {
    if (shader_id_) {
      GL_CHECK(glDeleteShader(shader_id_));
      this->shader_id_ = 0;
    }
  }

}  // namespace Shaders
