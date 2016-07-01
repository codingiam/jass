// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/states/states_manager.h"

#include "jass/states/state.h"

#include "jass/states/intro.h"
#include "jass/states/play.h"

namespace States {

StatesManager::StatesManager() {
}


StatesManager::~StatesManager() {
  ShutDown();
}

void StatesManager::Initialize() {
  this->state_intro_ = std::make_shared<Intro>();
  this->state_play_ = std::make_shared<Play>();

  State::Register(kIntro, state_intro_);
  State::Register(kPlay, state_play_);

  State::SetState(state_intro_.get());
  State::Swap();
}

void StatesManager::ShutDown() {
  State::Unregister(kPlay);
  State::Unregister(kIntro);
}

}  // namespace States
