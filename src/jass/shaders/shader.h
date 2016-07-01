// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <GL/glew.h>

#include <string>

namespace Shaders {

class Shader {
 public:
  explicit Shader(std::string const &path);
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
  std::string path_;
};

}  // namespace Shaders
