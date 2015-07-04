// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/states_manager.h"

#include "jass/state.h"

#include "jass/state_intro.h"
#include "jass/state_play.h"

StatesManager::StatesManager() {
}


StatesManager::~StatesManager() {
}

void StatesManager::Initialize(Video *const video) {
  this->state_intro_ = std::shared_ptr<StateIntro>(new StateIntro());
  this->state_play_ = std::shared_ptr<StatePlay>(new StatePlay());

  State::Register(kStateIntro, state_intro_, video);
  State::Register(kStatePlay, state_play_, video);

  State::SetState(state_intro_.get());
  State::Swap();
}

void StatesManager::ShutDown() {
  State::Unregister(kStatePlay);
  State::Unregister(kStateIntro);
}
