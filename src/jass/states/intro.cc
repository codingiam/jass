// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/states/intro.h"

#include "jass/application.h"
#include "jass/states/states_manager.h"
#include "jass/subsystems/window.h"
#include "jass/resources/image.h"

#include "jass/game_objects/intro/background.h"
#include "jass/game_objects/intro/title.h"
#include "jass/game_objects/intro/text.h"
#include "jass/game_objects/intro/menu.h"

namespace States {

Intro::Intro() {
}

Intro::~Intro() {
  bg_space_.reset();
  bg_intro_.reset();
  bg_intro_text_.reset();
  bg_action_.reset();
}

void Intro::Create() {
  this->bg_space_ =
      std::make_shared<GameObjects::Intro::Background>();
  this->bg_space_->Create();

  this->bg_intro_ =
      std::make_shared<GameObjects::Intro::Title>();
  this->bg_intro_->Create();

  this->bg_intro_text_ =
      std::make_shared<GameObjects::Intro::Text>();
  this->bg_intro_text_->Create();

  this->bg_action_ =
      std::make_shared<GameObjects::Intro::Menu>();
  this->bg_action_->Create();
}

void Intro::Start() {
  bg_intro_->Start();
  bg_intro_text_->Start();
  bg_action_->Start();
}

void Intro::Stop() {
}

void Intro::Update(const double dt, const bool *keys_states) {
  bg_intro_->Update(dt);
  bg_intro_text_->Update(dt);
  bg_action_->Update(dt);

  if (keys_states[GLFW_KEY_SPACE])
    State::SetState(State::Find(States::kPlay).lock().get());

  if (keys_states[GLFW_KEY_F10])
    State::SetState(NULL);
}

void Intro::Render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  bg_space_->Render();
  bg_intro_->Render();
  bg_intro_text_->Render();
  bg_action_->Render();
}

}  // namespace States
