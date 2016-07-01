// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef font_drawable_h
#define font_drawable_h

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

class Font : public Drawable {
 public:
  explicit Font(std::string const &path);
  virtual ~Font(void);

  void Create(void) override;
  void Render(void) override;

  void text(const std::string &text) {
    this->text_ = text;
  }

 private:
  std::shared_ptr<Shaders::Program> program_;

  std::shared_ptr<GL::Texture> texture_;

  std::string path_;

  std::string text_;

  std::shared_ptr<GL::VertexArrayObject> vao_;
  std::shared_ptr<GL::VertexBufferObject> vbo_;
};

}  // namespace Drawables

#endif /* font_drawable_h */
