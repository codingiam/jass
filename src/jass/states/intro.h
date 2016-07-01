// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATE_INTRO_H_
#define JASS_STATE_INTRO_H_
#pragma once

#include "jass/states/state.h"

#include "jass/jass.h"

namespace GameObjects {
namespace Intro {
class Background;
class Title;
class Text;
class Menu;
}
}

namespace States {

class Intro : public State {
 public:
  Intro(void);
  ~Intro(void);

  void Update(const Uint32 dt, const Uint8 *keystate) override;
  void Render(Video *const video) override;

 protected:
  void Create(void) override;
  void Start(void) override;
  void Stop(void) override;

 private:
  std::shared_ptr<GameObjects::Intro::Background> bg_space_;
  std::shared_ptr<GameObjects::Intro::Title> bg_intro_;
  std::shared_ptr<GameObjects::Intro::Menu> bg_action_;
  std::shared_ptr<GameObjects::Intro::Text> bg_intro_text_;
};

}  // namespace States

#endif  // JASS_STATE_INTRO_H_
