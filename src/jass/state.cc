// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/state.h"

#include <cassert>
#include <string>
#include <map>
#include <utility>

#include "jass/state_intro.h"

State* State::state_ = NULL;
State* State::next_ = NULL;

std::map<std::string, boost::weak_ptr<State> > State::states_;

void State::Register(const std::string& name,
                     const boost::weak_ptr<State>& state,
                     Video *const video) {
  const std::map<std::string, boost::weak_ptr<State> >::iterator it =
    states_.find(name);

  if (it != states_.end())
    throw(std::runtime_error("State already registered."));

  state.lock()->Create();
  states_.insert(std::pair<std::string, boost::weak_ptr<State> >(name, state));
}

boost::weak_ptr<State> State::Find(const std::string& name) {
  boost::weak_ptr<State> state;

  const std::map<std::string, boost::weak_ptr<State> >::iterator it =
    states_.find(name);
  if (it != states_.end())
    state = it->second;

  return state;
}

boost::weak_ptr<State> State::Unregister(const std::string& name) {
  boost::weak_ptr<State> state;

  const std::map<std::string, boost::weak_ptr<State> >::iterator it =
    states_.find(name);
  if (it != states_.end()) {
    state = it->second;
    states_.erase(it);
    state.lock()->Destroy();
  }

  return state;
}

void State::Update() {
  if (state_ != next_) {
    if (state_)
      state_->Stop();

    state_ = next_;

    if (state_)
      state_->Start();
  }
}

void State::SetState(State* state) {
    next_ = state;
}
