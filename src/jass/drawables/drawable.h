// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "jass/jass.h"

class Video;

namespace Drawables {

class Drawable : private boost::noncopyable {
 public:
  Drawable(void);
  virtual ~Drawable(void);

  virtual void Create(void) = 0;
  virtual void Render(Video *const video) = 0;

  void position(const glm::vec3 &position) {
    this->position_ = position;
  }

  glm::vec3 position(void) {
    return position_;
  }

  void scale(const glm::vec3 &scale) {
    this->scale_ = scale;
  }

  glm::vec3 scale(void) {
    return scale_;
  }

  void color(const glm::vec4 &color) {
    this->color_ = color;
  }

  glm::vec4 color(void) {
    return color_;
  }

 private:
  glm::vec3 position_;
  glm::vec3 scale_;
  glm::vec4 color_;
};

}  // namespace Drawables
