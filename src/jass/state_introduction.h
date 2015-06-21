// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_STATE_INTRODUCTION_H_
#define JASS_SRC_JASS_STATE_INTRODUCTION_H_
#pragma once

#include "jass/state.h"

#include "jass/jass.h"

class StateIntro : public State {
public:
  StateIntro(void);
  virtual ~StateIntro(void);

  void Execute(const Uint32 dt, const Uint8 *keystate) override;
  void Render(Video *const video) override;

protected:
  void Create(void) override;
  void Start(void) override;
  void Stop(void) override;

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

  float alphaTitle;
  float blueAction;
  float positionText;

  Uint32 showTo;

  Uint32 sizeIntroText;
};

#endif  // JASS_SRC_JASS_STATE_INTRODUCTION_H_
