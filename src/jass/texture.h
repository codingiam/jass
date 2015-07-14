// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/jass.h"

class Image;

class Texture : private boost::noncopyable {
 public:
  Texture(void);
  ~Texture(void);

  bool LoadTexture(std::shared_ptr<Image> const &image);

  static std::shared_ptr<Texture> MakeTexture(
    std::shared_ptr<Image> const &image);

  bool Bind(std::function<void(void)> const &func);

  // TODO(Doru): Deprecate this.
  bool Bind(void);

 private:
  GLuint texture_;
};
