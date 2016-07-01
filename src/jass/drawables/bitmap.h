// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <string>

#include "jass/drawables/drawable.h"

class Video;
class Texture;
class VertexArrayObject;
class BufferObject;

namespace Shaders {
class Program;
}

namespace Drawables {

class Bitmap : public Drawable {
 public:
  explicit Bitmap(std::string const &path);
  virtual ~Bitmap(void);

  void Create(void) override;
  void Render(Video *const video) override;

  GLfloat width(void) { return width_; }
  GLfloat height(void) { return height_; }

 private:
  std::shared_ptr<Shaders::Program> program_;

  std::shared_ptr<Texture> texture_;

  std::string path_;

  GLfloat width_;
  GLfloat height_;

  std::shared_ptr<VertexArrayObject> vao_;
  std::shared_ptr<BufferObject> vbo_;
};

}  // namespace Drawables
