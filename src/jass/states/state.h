// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATE_H_
#define JASS_STATE_H_
#pragma once

#include <map>
#include <string>
#include <memory>

namespace States {

class State {
 public:
  State(const State &) = delete;
  State & operator=(const State &) = delete;

  State(void) { }
  virtual ~State(void) { }

  virtual void Create(void) = 0;
  virtual void Start(void) = 0;
  virtual void Update(const uint32_t dt, const uint8_t *keystate) = 0;
  virtual void Render(void) = 0;
  virtual void Stop(void) = 0;
  virtual void Destroy(void) { }

  static void Swap(void);

  static void SetState(State *state);
  static State* GetState(void) { return state_; }

  static void Register(const std::string &name,
    const std::weak_ptr<State> &state);
  static std::weak_ptr<State> Find(const std::string &name);
  static std::weak_ptr<State> Unregister(const std::string &name);

 private:
  static std::map<std::string, std::weak_ptr<State> > states_;

  static State *state_;
  static State *next_;
};

}  // namespace States

#endif  // JASS_STATE_H_
