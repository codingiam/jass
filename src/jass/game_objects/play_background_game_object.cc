// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/play_background_game_object.h"

#include "jass/drawables/bitmap_drawable.h"

namespace GameObjects {

  PlayBackgroundGameObject::PlayBackgroundGameObject() {
  }

  PlayBackgroundGameObject::~PlayBackgroundGameObject() {
    bg_space_.reset();
  }

  void PlayBackgroundGameObject::Create() {
    this->bg_space_ = std::make_shared<Drawables::BitampDrawable>("resources/textures/spacebg.png");
    this->bg_space_->Create();
  }

  void PlayBackgroundGameObject::Render(Video *const video) {
    bg_space_->translation(glm::vec3(0, 0, 0));
    bg_space_->scale(glm::vec3(800.0 / bg_space_->width(), 600.0 / bg_space_->height(), 1.0));
    bg_space_->Render(video);
  }

}  // namespace GameObjects
