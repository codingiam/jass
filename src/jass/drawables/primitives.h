// Copyright (c) 2016, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_PRIMITIVES_DRAWABLE_H
#define JASS_PRIMITIVES_DRAWABLE_H

#include <vector>

#include "jass/drawables/drawable.h"

class Video;
class VertexArrayObject;
class BufferObject;

namespace Shaders {
class Program;
}

namespace Drawables {

class Primitives : public Drawable {
 public:
  Primitives(void);
  virtual ~Primitives(void);

  void Create(void) override;
  void Render(Video *const video) override;

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
  std::shared_ptr<Shaders::Program> program_;
  std::shared_ptr<VertexArrayObject> vao_;
  std::shared_ptr<BufferObject> vbo_;

  GLfloat point_size_;
  std::vector<glm::vec2> vertices_;
  std::vector<glm::vec3> colors_;
};

}  // namespace Drawables

#endif  // JASS_PRIMITIVES_DRAWABLE_H
