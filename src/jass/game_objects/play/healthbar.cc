// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be

#include "jass/game_objects/play/healthbar.h"

#include "jass/drawables/bitmap.h"

#include "jass/game_objects/play/ship.h"

namespace GameObjects {
namespace Play {

Healthbar::Healthbar(const int x, const int y,
    const int w, const int h, std::shared_ptr<GameObject> const &parent) :
    GameObject(parent), x_(x), y_(y), w_(w), h_(h)
{
  this->life_ = 0;
}

Healthbar::~Healthbar() {
}

void Healthbar::Create() {
  this->bg_healthbar_ =
      std::make_shared<Drawables::Bitmap>("resources/textures/healthbar.png");
  this->bg_healthbar_->Create();
}

void Healthbar::Start() {
}

void Healthbar::Update(const Uint32 dt) {
  this->life_ =
      std::static_pointer_cast<Ship>(parent_.lock())->GetLife();
}

void Healthbar::Render(Video *const video) {
  bg_healthbar_->color(glm::vec4(1.0f, life_, life_, 0.5f));
  bg_healthbar_->translation(glm::vec3(x_, y_, 0));
  bg_healthbar_->scale(glm::vec3(w_ / bg_healthbar_->width(),
      h_ / bg_healthbar_->height(), 1.0));
  bg_healthbar_->Render(video);
}

}  // namespace Play
}  // namespace GameObjects
