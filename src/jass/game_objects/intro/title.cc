// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/intro/title.h"

#include "jass/drawables/bitmap.h"

namespace GameObjects {
namespace Intro {

Title::Title() {
  this->alpha_title_ = 0;
  this->ticks_title_ = 0;
  this->speed_title_ = 1 * 1000;
}

Title::~Title() {
  bg_intro_.reset();
}

void Title::Start() {
  this->alpha_title_ = 0;
  this->ticks_title_ = 0;
}

void Title::Create() {
  this->bg_intro_ =
      std::make_shared<Drawables::Bitmap>("resources/textures/title.png");
  this->bg_intro_->Create();
}

void Title::Update(const Uint32 dt) {
  this->ticks_title_ += dt;
  this->alpha_title_ = static_cast<float>(ticks_title_) / speed_title_;
  if (alpha_title_ >= 1.0f) this->alpha_title_ = 1.0f;
}

void Title::Render(Video *const video) {
  bg_intro_->translation(glm::vec3(272, 8, 0));
  bg_intro_->color(glm::vec4(1.0f, 1.0f, 1.0f, alpha_title_));
  bg_intro_->Render(video);
}

}  // namespace Intro
}  // namespace GameObjects
