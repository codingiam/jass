// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <string>

#include "jass/jass.h"

namespace Shaders {

class Shader {
 public:
  Shader(void);
  virtual ~Shader(void);

  virtual void Create(void) = 0;

  GLuint shader_id(void) {
    return shader_id_;
  }

 protected:
  void Create(const GLenum shader_type, const std::string &source);

 private:
  GLuint shader_id_;
};

}  // namespace Shaders
