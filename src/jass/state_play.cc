// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/state_play.h"

#include <vector>
#include <array>
#include <cmath>

#include "jass/video.h"
#include "jass/application.h"
#include "jass/states_manager.h"
#include "jass/play_projectile_game_object.h"
#include "jass/window.h"
#include "jass/image.h"
#include "jass/texture.h"

#include "jass/play_background_game_object.h"
#include "jass/play_healthbar_game_object.h"
#include "jass/play_ship_game_object.h"
#include "jass/play_board_game_object.h"

StatePlay::StatePlay() {
}

StatePlay::~StatePlay() {
  bg_space_.reset();
  red_ship_healthbar_.reset();
  blue_ship_healthbar_.reset();
  red_ship_.reset();
  blue_ship_.reset();
  bg_board_.reset();
  projectiles_.clear();
}

void StatePlay::Create() {
  this->bg_space_ = std::make_shared<GameObjects::PlayBackgroundGameObject>();
  this->bg_space_->Create();

  std::array<Uint32, 6> keys1 = { SDL_SCANCODE_Q, SDL_SCANCODE_S, SDL_SCANCODE_C,
    SDL_SCANCODE_V, SDL_SCANCODE_LCTRL, 0 };

  std::array<Uint32, 6> keys2 = { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL, 0 };

  this->red_ship_ = std::make_shared<GameObjects::PlayShipGameObject>(-4.5f, 3.25f, 1, 0.0f, keys1);
  this->red_ship_->Create();

  this->blue_ship_ = std::make_shared<GameObjects::PlayShipGameObject>(4.5f, -2.40f, 2, 180.0f, keys2);
  this->blue_ship_->Create();

  this->red_ship_healthbar_ = std::make_shared<GameObjects::PlayHealthbarGameObject>(10, 10, 20, 512, red_ship_);
  this->red_ship_healthbar_->Create();

  this->blue_ship_healthbar_ = std::make_shared<GameObjects::PlayHealthbarGameObject>(770, 10, 20, 512, blue_ship_);
  this->blue_ship_healthbar_->Create();

  this->bg_board_ = std::make_shared<GameObjects::PlayBoardGameObject>();
  this->bg_board_->Create();
}

void StatePlay::Start() {
  red_ship_->Start();
  blue_ship_->Start();
}

void StatePlay::Stop() {
  projectiles_.clear();
}

void StatePlay::Update(const Uint32 dt, const Uint8 *keystate) {
  for (auto it = projectiles_.begin(); it != projectiles_.end(); ) {
    auto p = *it;   

    p->Update(dt);

    if ((p->owner_ == 1 && blue_ship_->Collide(p->xpos_, p->ypos_)) ||
        (p->owner_ == 2 && red_ship_->Collide(p->xpos_, p->ypos_)) ||
        (std::abs(p->xpos_) >= 6.5f || std::abs(p->ypos_) >= 5.5f)) {
      it = projectiles_.erase(it);
    } else {
      ++it;
    }
  }

  red_ship_->Update(dt, keystate);
  blue_ship_->Update(dt, keystate);

  blue_ship_healthbar_->Update(dt);
  red_ship_healthbar_->Update(dt);

  if (keystate[SDL_SCANCODE_ESCAPE]) {
      State::SetState(State::Find(kStateIntro).lock().get());
  }

  if ((red_ship_->GetLife() <= 0.0f) || (blue_ship_->GetLife() <= 0.0f)) {
    State::SetState(State::Find(kStateIntro).lock().get());
  }
}

void StatePlay::AddProjectile(const GLfloat xpos, const GLfloat ypos, const GLfloat angle, const GLuint owner) {
  projectiles_.push_back(std::make_shared<GameObjects::PlayProjectileGameObject>(xpos, ypos, angle, owner));
}

void StatePlay::Render(Video *const video) {
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
  video->Init2DScene(Window::kWidth, Window::kHeight);

  bg_space_->Render(video);

  video->Init3DScene(Window::kWidth, Window::kHeight);

  red_ship_->Render(video);
  blue_ship_->Render(video);

  for (auto it = projectiles_.begin(); it != projectiles_.end(); ++it) {
    (*it)->Render(video);
  }

  video->Init2DScene(Window::kWidth, Window::kHeight);

  blue_ship_healthbar_->Render(video);
  red_ship_healthbar_->Render(video);
  
  bg_board_->Render(video);
}
