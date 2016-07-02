// Copyright (c) 2016, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_PRIMITIVES_DRAWABLE_H
#define JASS_PRIMITIVES_DRAWABLE_H

#include <GL/glew.h>

#include <vector>
#include <memory>

#include "jass/drawables/drawable.h"

namespace GL {
class VertexArrayObject;
class VertexBufferObject;
class Program;
}

namespace Drawables {

class Primitives : public Drawable {
 public:
  Primitives(void);
  virtual ~Primitives(void);

  void Create(void) override;
  void Render(void) override;

  void point_size(GLfloat const point_size) {
    this->point_size_ = point_size;
  }

  void vertices(std::vector<glm::vec2> && vertices) {
    this->vertices_ = std::move(vertices);
  }

  void colors(std::vector<glm::vec3> && colors) {
    this->colors_ = std::move(colors);
  }

 private:
  std::shared_ptr<GL::Program> program_;
  std::shared_ptr<GL::VertexArrayObject> vao_;
  std::shared_ptr<GL::VertexBufferObject> vbo_;

  GLfloat point_size_;
  std::vector<glm::vec2> vertices_;
  std::vector<glm::vec3> colors_;
};

}  // namespace Drawables

#endif  // JASS_PRIMITIVES_DRAWABLE_H
