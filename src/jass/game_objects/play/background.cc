// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/play/background.h"

#include "jass/drawables/bitmap.h"

namespace GameObjects {
namespace Play {

Background::Background() {
}

Background::~Background() {
  bg_space_.reset();
}

void Background::Create() {
  this->bg_space_ =
      std::make_shared<Drawables::Bitmap>("resources/textures/spacebg.png");
  this->bg_space_->Create();
}

void Background::Render(Video *const video) {
  bg_space_->translation(glm::vec3(0, 0, 0));
  bg_space_->scale(glm::vec3(800.0 / bg_space_->width(),
      600.0 / bg_space_->height(), 1.0));
  bg_space_->Render(video);
}

}  // namespace Play
}  // namespace GameObjects
