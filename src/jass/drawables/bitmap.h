// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_DRAWABLES_BITMAP_H_
#define JASS_DRAWABLES_BITMAP_H_

#include <GL/glew.h>

#include <boost/filesystem.hpp>

#include <string>
#include <memory>

#include "jass/drawables/drawable.h"

namespace GL {
class VertexArrayObject;
class VertexBufferObject;
class Texture;
class Program;
}

namespace Drawables {

class Bitmap : public Drawable {
 public:
  explicit Bitmap(boost::filesystem::path const &path);
  virtual ~Bitmap(void);

  void Create(void) override;
  void Render(void) override;

  GLfloat width(void) { return width_; }
  GLfloat height(void) { return height_; }

 private:
  std::shared_ptr<GL::Program> program_;

  std::shared_ptr<GL::Texture> texture_;

  boost::filesystem::path path_;

  GLfloat width_;
  GLfloat height_;

  std::shared_ptr<GL::VertexArrayObject> vao_;
  std::shared_ptr<GL::VertexBufferObject> vbo_;
};

}  // namespace Drawables

#endif  // JASS_DRAWABLES_BITMAP_H_
