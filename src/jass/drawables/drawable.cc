// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/drawable.h"

namespace Drawables {

  Drawable::Drawable() {
    this->scale_ = glm::vec3(1.0);
    this->color_ = glm::vec4(1.0);
  }

  Drawable::~Drawable() {
  }

}  // namespace Drawables
