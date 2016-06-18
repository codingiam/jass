// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/states/states_manager.h"

#include "jass/states/state.h"

#include "jass/states/state_intro.h"
#include "jass/states/state_play.h"

namespace States {

StatesManager::StatesManager() {
}


StatesManager::~StatesManager() {
}

void StatesManager::Initialize(Video *const video) {
  this->state_intro_ = std::make_shared<StateIntro>();
  this->state_play_ = std::make_shared<StatePlay>();

  State::Register(kStateIntro, state_intro_, video);
  State::Register(kStatePlay, state_play_, video);

  State::SetState(state_play_.get());
  State::Swap();
}

void StatesManager::ShutDown() {
  State::Unregister(kStatePlay);
  State::Unregister(kStateIntro);
}

}  // namespace States
