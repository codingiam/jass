// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/space_background_game_object.h"

#include "jass/window.h"

#include "jass/video.h"
#include "jass/image.h"
#include "jass/texture.h"

namespace GameObjects {

  SpaceBackgroundGameObject::SpaceBackgroundGameObject() {
  }

  SpaceBackgroundGameObject::~SpaceBackgroundGameObject() {
    bg_space_.reset();
  }

  void SpaceBackgroundGameObject::Create() {
    std::shared_ptr<Image> image = Image::MakeImage("data/texturi/introbg.png");
    this->bg_space_ = Texture::MakeTexture(image);
  }

  void SpaceBackgroundGameObject::Render(Video *const video) {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    video->DrawTexture(0, 0, Window::kWidth, Window::kHeight, bg_space_);
  }

}
