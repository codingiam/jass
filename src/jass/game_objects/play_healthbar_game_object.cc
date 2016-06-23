// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be

#include "jass/game_objects/play_healthbar_game_object.h"

#include "jass/drawables/bitmap_drawable.h"

#include "jass/game_objects/play_ship_game_object.h"

namespace GameObjects {

  PlayHealthbarGameObject::PlayHealthbarGameObject(const int x, const int y, const int w, const int h,
    std::shared_ptr<GameObject> const &parent) : GameObject(parent), x_(x), y_(y), w_(w), h_(h)
  {
    this->life_ = 0;
  }

  PlayHealthbarGameObject::~PlayHealthbarGameObject() {
  }

  void PlayHealthbarGameObject::Create() {
    this->bg_healthbar_ = std::make_shared<Drawables::BitampDrawable>("data/textures/healthbar.png");
    this->bg_healthbar_->Create();
  }

  void PlayHealthbarGameObject::Start() {
  }

  void PlayHealthbarGameObject::Update(const Uint32 dt) {
    this->life_ = std::static_pointer_cast<PlayShipGameObject>(parent_.lock())->GetLife();
  }

  void PlayHealthbarGameObject::Render(Video *const video) {
    bg_healthbar_->color(glm::vec4(1.0f, life_, life_, 0.5f));
    bg_healthbar_->translation(glm::vec3(x_, y_, 0));
    bg_healthbar_->scale(glm::vec3(w_ / bg_healthbar_->width(), h_ / bg_healthbar_->height(), 1.0));
    bg_healthbar_->Render(video);
  }

}  // namespace GameObjects
