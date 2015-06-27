// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATE_H_
#define JASS_STATE_H_
#pragma once

#include <boost/weak_ptr.hpp>

#include <map>
#include <string>

#include "jass/jass.h"

class Video;

class State : boost::noncopyable {
 public:
  State(void) { }
  virtual ~State(void) { }

  virtual void Create(void) = 0;
  virtual void Start(void) = 0;
  virtual void Update(const Uint32 dt, const Uint8 *keystate) = 0;
  virtual void Render(Video *const video) = 0;
  virtual void Stop(void) = 0;
  virtual void Destroy(void) { }

  static void Swap(void);

  static void SetState(State *state);
  static State* GetState(void) { return state_; }

  static void Register(const std::string &name,
    const boost::weak_ptr<State> &state,
    Video *const video);
  static boost::weak_ptr<State> Find(const std::string &name);
  static boost::weak_ptr<State> Unregister(const std::string &name);

 private:
  static std::map<std::string, boost::weak_ptr<State> > states_;

  static State *state_;
  static State *next_;
};

#endif  // JASS_STATE_H_
