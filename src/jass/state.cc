// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/state.h"

#include <cassert>
#include <string>
#include <map>

#include "jass/state_introduction.h"

State* State::state_ = NULL;
State* State::next_ = NULL;

std::map<std::string, boost::weak_ptr<State>> State::states;

void State::Register(const std::string& name, const boost::weak_ptr<State>& state) {
  const std::map<std::string, boost::weak_ptr<State>>::iterator it = states.find(name); 

  if (it != states.end())
    throw(std::runtime_error("State already registered."));

  state.lock()->Create();
  states.insert(std::pair<std::string, boost::weak_ptr<State>>(name, state));
}

boost::weak_ptr<State> State::Find(const std::string& name) {
  boost::weak_ptr<State> state;

  const std::map<std::string, boost::weak_ptr<State>>::iterator it = states.find(name); 
  if (it != states.end())
    state = it->second;

  return state;
}

boost::weak_ptr<State> State::Unregister(const std::string& name) {
  boost::weak_ptr<State> state;

  const std::map<std::string, boost::weak_ptr<State>>::iterator it = states.find(name); 
  if (it != states.end()) {
    state = it->second;
    states.erase(it);
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

void State::set_state(State* state) {
    next_ = state;
}
