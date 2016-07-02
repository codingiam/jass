// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_INTRO_MENU_H_
#define JASS_GAME_OBJECTS_INTRO_MENU_H_

#include "jass/game_objects/game_object.h"

namespace Drawables {
class Bitmap;
}

namespace GameObjects {
namespace Intro {

class Menu : public GameObject {
 public:
  Menu(void);
  ~Menu(void);

  void Create(void) override;
  void Start(void) override;

  void Update(const uint32_t dt) override;
  void Render(void) override;

 private:
  std::shared_ptr<Drawables::Bitmap> bg_action_;

  uint32_t ticks_action_;

  uint32_t speed_action_;

  float blue_action_;
};

}  // namespace Intro
}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_INTRO_MENU_H_
