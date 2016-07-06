// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/gl/shader.h"

#include <boost/format.hpp>

#include <fstream>
#include <iterator>
#include <vector>

namespace GL {

Shader::Shader(boost::filesystem::path const &path) {
  this->path_ = path;
  this->shader_id_ = 0;
}

void Shader::Create(const GLenum shader_type) {
  this->shader_id_ = glCreateShader(shader_type);

  const std::string source = LoadSource();

  char const *source_str = source.c_str();
  glShaderSource(shader_id_, 1, &source_str, NULL);

  glCompileShader(shader_id_);

  GLint result = GL_FALSE;
  glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &result);

  if (result != GL_TRUE) {
    GLint log_length;

    glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
      std::unique_ptr<GLchar[]> error_message = std::make_unique<GLchar[]>(log_length);

      glGetShaderInfoLog(shader_id_, log_length, NULL, error_message.get());

      fprintf(stderr, "%s\n", error_message.get());
    }

    boost::format message =
      boost::format("Could not compile shader: %s") % path_;
    throw std::runtime_error(message.str());
  }
}

std::string Shader::LoadSource() {
  std::ifstream data_source { path_.c_str(), std::ifstream::in };
  if (!data_source.is_open()) {
    boost::format message =
      boost::format("Could not load shader: %s") % path_;
    throw std::runtime_error(message.str());
  }
  std::string source { std::istreambuf_iterator<char>(data_source),
      std::istreambuf_iterator<char>() };
  return source;
}

Shader::~Shader() {
  if (shader_id_) {
    glDeleteShader(shader_id_);
    this->shader_id_ = 0;
  }
}

}  // namespace GL
