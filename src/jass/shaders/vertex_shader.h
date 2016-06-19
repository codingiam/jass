// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/shaders/shader.h"

namespace Shaders {

class VertexShader : public Shader {
 public:
  VertexShader(void);
  ~VertexShader(void);

  void Create(void) override;
};

}  // namespace Shaders
