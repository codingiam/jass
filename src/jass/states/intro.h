// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATES_INTRO_H_
#define JASS_STATES_INTRO_H_

#include "jass/states/state.h"

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

  void Update(const double dt, const bool *keys_states) override;
  void Render(void) override;

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

#endif  // JASS_STATES_INTRO_H_
