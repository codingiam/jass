// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <GL/glew.h>

#include <memory>

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
