// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/state_intro.h"

#include "jass/video.h"
#include "jass/application.h"
#include "jass/states_manager.h"
#include "jass/window.h"
#include "jass/image.h"
#include "jass/texture.h"

#include "jass/intro_background_game_object.h"
#include "jass/intro_title_game_object.h"
#include "jass/intro_text_game_object.h"
#include "jass/intro_menu_game_object.h"

StateIntro::StateIntro() {
}

StateIntro::~StateIntro() {
  bg_space_.reset();
  bg_intro_.reset();
  bg_intro_text_.reset();
  bg_action_.reset();
}

void StateIntro::Create() {
  this->bg_space_ = std::make_shared<GameObjects::IntroBackgroundGameObject>();
  this->bg_space_->Create();

  this->bg_intro_ = std::make_shared<GameObjects::IntroTitleGameObject>();
  this->bg_intro_->Create();

  this->bg_intro_text_ = std::make_shared<GameObjects::IntroTextGameObject>();
  this->bg_intro_text_->Create();

  this->bg_action_ = std::make_shared<GameObjects::IntroMenuGameObject>();
  this->bg_action_->Create();
}

void StateIntro::Start() {
  bg_intro_->Start();
  bg_intro_text_->Start();
  bg_action_->Start();
}

void StateIntro::Stop() {
}

void StateIntro::Update(const Uint32 dt, const Uint8 *keystate) {
  bg_intro_->Update(dt);
  bg_intro_text_->Update(dt);
  bg_action_->Update(dt);

  if (keystate[SDL_SCANCODE_SPACE])
      State::SetState(State::Find(kStatePlay).lock().get());

  if (keystate[SDL_SCANCODE_F10])
      State::SetState(NULL);
}

void StateIntro::Render(Video *const video) {
  glClear(GL_COLOR_BUFFER_BIT);

  video->Init2DScene(Window::kWidth, Window::kHeight);

  bg_space_->Render(video);
  bg_intro_->Render(video);
  bg_intro_text_->Render(video);
  bg_action_->Render(video);
}
