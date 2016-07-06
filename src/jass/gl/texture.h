// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GL_TEXTURE_H_
#define JASS_GL_TEXTURE_H_

#include <GL/glew.h>

#include <memory>
#include <functional>

namespace Resources {
class Image;
}

namespace GL {

class Texture {
 public:
  Texture(const Texture &) = delete;
  Texture & operator=(const Texture &) = delete;

  Texture(void);
  ~Texture(void);

  bool LoadTexture(std::shared_ptr<Resources::Image> const &image);

  static std::shared_ptr<Texture> MakeTexture(
    std::shared_ptr<Resources::Image> const &image);

  bool Bind(std::function<void(void)> const &func);

  // TODO(Doru): Deprecate this.
  bool Bind(void);

 private:
  GLuint texture_;
};

}  // namespace GL

#endif  // JASS_GL_TEXTURE_H_
