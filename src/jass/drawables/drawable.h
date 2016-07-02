// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_DRAWABLES_DRAWABLE_H_
#define JASS_DRAWABLES_DRAWABLE_H_

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Drawables {

class Drawable {
 public:
  Drawable(const Drawable &) = delete;
  Drawable & operator=(const Drawable &) = delete;

  Drawable(void);
  virtual ~Drawable(void);

  virtual void Create(void) = 0;
  virtual void Render(void) = 0;

  void translation(const glm::vec3 &translation) {
    this->translation_ = translation;
  }

  glm::vec3 translation(void) {
    return translation_;
  }

  void scale(const glm::vec3 &scale) {
    this->scale_ = scale;
  }

  glm::vec3 scale(void) {
    return scale_;
  }

  void rotation(const glm::quat &rotation) {
    this->rotation_ = rotation;
  }

  glm::quat rotation(void) {
    return rotation_;
  }

  void color(const glm::vec4 &color) {
    this->color_ = color;
  }

  glm::vec4 color(void) {
    return color_;
  }

 private:
  glm::vec3 translation_;
  glm::quat rotation_;
  glm::vec3 scale_;

  glm::vec4 color_;
};

}  // namespace Drawables

#endif  // JASS_DRAWABLES_DRAWABLE_H_
