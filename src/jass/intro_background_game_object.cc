// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/intro_background_game_object.h"

#include "jass/bitmap_drawable.h"

namespace GameObjects {

  IntroBackgroundGameObject::IntroBackgroundGameObject() {
  }

  IntroBackgroundGameObject::~IntroBackgroundGameObject() {
    bg_space_.reset();
  }

  void IntroBackgroundGameObject::Create() {
    this->bg_space_ = std::make_shared<Drawables::BitampDrawable>("data/texturi/introbg.png");
    this->bg_space_->Create();
  }

  void IntroBackgroundGameObject::Render(Video *const video) {
    bg_space_->position(glm::vec3(0, 0, 0));
    bg_space_->Render(video);
  }

}
