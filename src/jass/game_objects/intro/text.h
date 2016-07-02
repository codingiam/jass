// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_INTRO_TEXT_H_
#define JASS_GAME_OBJECTS_INTRO_TEXT_H_

#include "jass/game_objects/game_object.h"

namespace Drawables {
class Font;
}

namespace GameObjects {
namespace Intro {

class Text : public GameObject {
 public:
  Text(void);
  ~Text(void);

  void Create(void) override;
  void Start(void) override;

  void Update(const double dt) override;
  void Render(void) override;

 private:
  std::shared_ptr<Drawables::Font> font_;

  double ticks_intro_text_;
  const double speed_intro_text_;

  double position_text_;

  uint32_t show_to_;

  const uint32_t size_intro_text_;
};

}  // namespace Intro
}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_INTRO_TEXT_H_
