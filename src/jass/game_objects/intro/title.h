// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_INTRO_TITLE_H_
#define JASS_GAME_OBJECTS_INTRO_TITLE_H_

#include "jass/game_objects/game_object.h"

namespace Drawables {
class Bitmap;
}

namespace GameObjects {
namespace Intro {

class Title : public GameObject {
 public:
  Title(void);
  ~Title(void);

  void Create(void) override;
  void Start(void) override;

  void Update(const double dt) override;
  void Render(void) override;

 private:
  std::shared_ptr<Drawables::Bitmap> bg_intro_;

  float alpha_title_;
  uint32_t ticks_title_;
  uint32_t speed_title_;
};

}  // namespace Intro
}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_INTRO_TITLE_H_
