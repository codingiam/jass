// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_STATE_H_
#define JASS_SRC_JASS_STATE_H_
#pragma once

#include <map>

#include <boost/weak_ptr.hpp>

#include "jass/jass.h"

class State : boost::noncopyable {
public:
  State() { }
  virtual ~State() { }

  virtual void Create() = 0;
  virtual void Start() = 0;
  virtual void Execute(Uint32 ticks, Uint8* keystate) = 0;
  virtual void Stop() = 0;
  virtual void Destroy() { }

  static void Update();
  
  static void set_state(State* state);
  static State* state() { return state_; }

  static void Register(const std::string& name, const boost::weak_ptr<State>& state);
  static boost::weak_ptr<State> Find(const std::string& name);
  static boost::weak_ptr<State> Unregister(const std::string& name);

private:
  static std::map<std::string, boost::weak_ptr<State>> states;
  static State* state_;
  static State* next_;
};

#endif  // JASS_SRC_JASS_STATE_H_
