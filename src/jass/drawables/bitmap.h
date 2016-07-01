// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <GL/glew.h>

#include <string>
#include <memory>

#include "jass/drawables/drawable.h"

namespace GL {
class VertexArrayObject;
class VertexBufferObject;
class Texture;
}

namespace Shaders {
class Program;
}

namespace Drawables {

class Bitmap : public Drawable {
 public:
  explicit Bitmap(std::string const &path);
  virtual ~Bitmap(void);

  void Create(void) override;
  void Render(void) override;

  GLfloat width(void) { return width_; }
  GLfloat height(void) { return height_; }

 private:
  std::shared_ptr<Shaders::Program> program_;

  std::shared_ptr<GL::Texture> texture_;

  std::string path_;

  GLfloat width_;
  GLfloat height_;

  std::shared_ptr<GL::VertexArrayObject> vao_;
  std::shared_ptr<GL::VertexBufferObject> vbo_;
};

}  // namespace Drawables
