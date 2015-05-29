// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_STATE_INTRODUCTION_H_
#define JASS_SRC_JASS_STATE_INTRODUCTION_H_
#pragma once

#include "jass/state.h"

#include "jass/jass.h"

static const std::string kStateIntro = "state_intro";

class StateIntro : public State {
public:
  StateIntro();
  virtual ~StateIntro();

  void Execute(Uint32 ticks, Uint8* keystate) override;

protected:
  void Create() override;
  void Start() override;
  void Stop() override;

private:
  GLuint bgSpace;
  GLuint bgIntro;
  GLuint bgAction;

  Uint32 ticksTitle;
  Uint32 ticksAction;
  Uint32 ticksIntroText;

  Uint32 speedTitle;
  Uint32 speedAction;
  Uint32 speedIntroText;

  Uint32 sizeIntroText;
};

#endif  // JASS_SRC_JASS_STATE_INTRODUCTION_H_
