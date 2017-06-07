// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GL_SHADER_H_
#define JASS_GL_SHADER_H_

#define GLSL(version, shader)  "#version " #version "\n" #shader

#include <glad/glad.h>

#include <boost/filesystem.hpp>

#include <string>

namespace GL {

class Shader {
 public:
  explicit Shader(boost::filesystem::path const &path);
  virtual ~Shader(void);

  virtual void Create(void) = 0;

  GLuint shader_id(void) {
    return shader_id_;
  }

 protected:
  void Create(const GLenum shader_type);

 private:
  std::string LoadSource(void);

  GLuint shader_id_;
  boost::filesystem::path path_;
};

}  // namespace GL

#endif  // JASS_GL_SHADER_H_
