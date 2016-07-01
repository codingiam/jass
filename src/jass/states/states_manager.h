// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATES_MANAGER_H_
#define JASS_STATES_MANAGER_H_
#pragma once

#include <string>

#include "jass/jass.h"

class Video;

namespace States {

class Intro;
class Play;

static const char kIntro[] = "state_intro";
static const char kPlay[] = "state_play";

class StatesManager {
 public:
  StatesManager(const StatesManager &) = delete;
  StatesManager & operator=(const StatesManager &) = delete;

  StatesManager(void);
  ~StatesManager(void);

  void Initialize(Video *const video);

 private:
  void ShutDown(void);

  std::shared_ptr<Intro> state_intro_;
  std::shared_ptr<Play> state_play_;
};

}  // namespace States

#endif  // JASS_STATES_MANAGER_H_
