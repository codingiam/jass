// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef font_drawable_h
#define font_drawable_h

#include <string>

#include "jass/drawables/drawable.h"

class Video;
class Texture;

namespace Shaders {
  class Program;
}

namespace Drawables {

class FontDrawable : public Drawable {
 public:
  FontDrawable(std::string const &path);
  virtual ~FontDrawable(void);

  void Create(void) override;
  void Render(Video *const video) override;

  void text(const std::string &text) {
    this->text_ = text;
  }

 private:
  std::shared_ptr<Shaders::Program> program_;

  std::shared_ptr<Texture> texture_;

  std::string path_;

  std::string text_;
};

}  // namespace Drawables

#endif /* font_drawable_h */
