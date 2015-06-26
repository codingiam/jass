// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATE_INTRO_H_
#define JASS_STATE_INTRO_H_
#pragma once

#include "jass/state.h"

#include "jass/jass.h"

class Texture;

class StateIntro : public State {
 public:
  StateIntro(void);
  ~StateIntro(void);

  void Execute(const Uint32 dt, const Uint8 *keystate) override;
  void Render(Video *const video) override;

 protected:
  void Create(void) override;
  void Start(void) override;
  void Stop(void) override;

 private:
  boost::shared_ptr<Texture> bg_space_;
  boost::shared_ptr<Texture> bg_intro_;
  boost::shared_ptr<Texture> bg_action_;

  Uint32 ticks_title_;
  Uint32 ticks_action_;
  Uint32 ticks_intro_text_;

  Uint32 speed_title_;
  Uint32 speed_action_;
  Uint32 speed_intro_text_;

  float alpha_title_;
  float blue_action_;
  float position_text_;

  Uint32 show_to_;

  Uint32 size_intro_text_;
};

#endif  // JASS_STATE_INTRO_H_
