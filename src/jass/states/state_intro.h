// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATE_INTRO_H_
#define JASS_STATE_INTRO_H_
#pragma once

#include "jass/states/state.h"

#include "jass/jass.h"

namespace GameObjects {
  class IntroBackgroundGameObject;
  class IntroTitleGameObject;
  class IntroTextGameObject;
  class IntroMenuGameObject;
}

namespace States {

class StateIntro : public State {
 public:
  StateIntro(void);
  ~StateIntro(void);

  void Update(const Uint32 dt, const Uint8 *keystate) override;
  void Render(Video *const video) override;

 protected:
  void Create(void) override;
  void Start(void) override;
  void Stop(void) override;

 private:
  std::shared_ptr<GameObjects::IntroBackgroundGameObject> bg_space_;
  std::shared_ptr<GameObjects::IntroTitleGameObject> bg_intro_; 
  std::shared_ptr<GameObjects::IntroMenuGameObject> bg_action_;
  std::shared_ptr<GameObjects::IntroTextGameObject> bg_intro_text_;
};

}

#endif  // JASS_STATE_INTRO_H_
