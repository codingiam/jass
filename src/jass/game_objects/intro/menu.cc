// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/intro/menu.h"

#include "jass/drawables/bitmap.h"

namespace GameObjects {
namespace Intro {

Menu::Menu() : speed_action_(2.0) {
}

Menu::~Menu() {
}

void Menu::Start() {
  this->ticks_action_ = 0;
}

void Menu::Create() {
  this->bg_action_ =
      std::make_shared<Drawables::Bitmap>("resources/textures/action.png");
  this->bg_action_->Create();
}

void Menu::Update(const double dt) {
  this->ticks_action_ += dt;

  this->blue_action_ = ticks_action_ / speed_action_;

  if (blue_action_ >= 1.0) this->ticks_action_ -= speed_action_;
}

void Menu::Render() {
  bg_action_->translation(glm::vec3(262, 440, 0));
  bg_action_->color(glm::vec4(1.0f, 1.0f - blue_action_, blue_action_, 1.0f));
  bg_action_->Render();
}

}  // namespace Intro
}  // namespace GameObjects
