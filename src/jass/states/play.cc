// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/states/play.h"

#include "jass/subsystems/video.h"
#include "jass/application.h"
#include "jass/states/states_manager.h"
#include "jass/subsystems/window.h"
#include "jass/resources/image.h"

#include "jass/game_objects/play/background.h"
#include "jass/game_objects/play/healthbar.h"
#include "jass/game_objects/play/ship.h"
#include "jass/game_objects/play/board.h"
#include "jass/game_objects/play/projectiles.h"

namespace States {

Play::Play() {
}

Play::~Play() {
  bg_space_.reset();
  red_ship_healthbar_.reset();
  blue_ship_healthbar_.reset();
  red_ship_.reset();
  blue_ship_.reset();
  bg_board_.reset();
  projectiles_.reset();
}

void Play::Create() {
  this->bg_space_ = std::make_shared<GameObjects::Play::Background>();
  this->bg_space_->Create();

  std::array<Uint32, 6> keys1 = { SDL_SCANCODE_Q, SDL_SCANCODE_S,
      SDL_SCANCODE_C, SDL_SCANCODE_V, SDL_SCANCODE_LCTRL, 0 };

  std::array<Uint32, 6> keys2 = { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN,
      SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL, 0 };

  this->red_ship_ =
      std::make_shared<GameObjects::Play::Ship>(-4.5f, 3.25f, 1,
          0.0f, keys1);
  this->red_ship_->Create();

  this->blue_ship_ =
      std::make_shared<GameObjects::Play::Ship>(4.5f, -2.40f, 2,
          180.0f, keys2);
  this->blue_ship_->Create();

  this->red_ship_healthbar_ =
      std::make_shared<GameObjects::Play::Healthbar>(10, 10, 20,
          512, red_ship_);
  this->red_ship_healthbar_->Create();

  this->blue_ship_healthbar_ =
      std::make_shared<GameObjects::Play::Healthbar>(770, 10, 20,
          512, blue_ship_);
  this->blue_ship_healthbar_->Create();

  this->bg_board_ = std::make_shared<GameObjects::Play::Board>();
  this->bg_board_->Create();

  this->projectiles_ =
      std::make_shared<GameObjects::Play::Projectiles>();
  this->projectiles_->Create();
}

void Play::Start() {
  red_ship_->Start();
  blue_ship_->Start();
}

void Play::Stop() {
  projectiles_->Clear();
}

void Play::Update(const Uint32 dt, const Uint8 *keystate) {
  red_ship_->Update(dt, keystate);
  blue_ship_->Update(dt, keystate);

  projectiles_->Update(dt, red_ship_.get(), blue_ship_.get());

  blue_ship_healthbar_->Update(dt);
  red_ship_healthbar_->Update(dt);

  if (keystate[SDL_SCANCODE_ESCAPE]) {
    State::SetState(States::State::Find(States::kIntro).lock().get());
    return;
  }

  if ((red_ship_->GetLife() <= 0.0f) || (blue_ship_->GetLife() <= 0.0f)) {
    State::SetState(States::State::Find(States::kIntro).lock().get());
  }
}

void Play::AddProjectile(const GLfloat xpos, const GLfloat ypos,
    const GLfloat angle, const GLuint owner) {
  projectiles_->AddProjectile(xpos, ypos, angle, owner);
}

void Play::Render(Video *const video) {
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

  video->Init2DScene(Window::kWidth, Window::kHeight);

  bg_space_->Render(video);

  video->Init3DScene(Window::kWidth, Window::kHeight);

  red_ship_->Render(video);
  blue_ship_->Render(video);

  projectiles_->Render(video);

  video->Init2DScene(Window::kWidth, Window::kHeight);

  blue_ship_healthbar_->Render(video);
  red_ship_healthbar_->Render(video);

  bg_board_->Render(video);
}

}  // namespace States
