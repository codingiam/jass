// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATES_MANAGER_H_
#define JASS_STATES_MANAGER_H_
#pragma once

#include <string>

#include "jass/jass.h"

class StateIntro;
class StatePlay;

static const std::string kStateIntro = "state_intro";
static const std::string kStatePlay = "state_play";

class StatesManager : boost::noncopyable {
 public:
  StatesManager(void);
  ~StatesManager(void);

  void Initialize(void);
  void ShutDown(void);

 private:
  boost::shared_ptr<StateIntro> state_intro_;
  boost::shared_ptr<StatePlay> state_play_;
};

#endif  // JASS_STATES_MANAGER_H_
