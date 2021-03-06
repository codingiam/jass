// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_INTRO_BACKGROUND_H_
#define JASS_GAME_OBJECTS_INTRO_BACKGROUND_H_

#include "jass/game_objects/game_object.h"

namespace Drawables {
class Bitmap;
}

namespace GameObjects {
namespace Intro {

class Background : public GameObject {
 public:
  Background(void);
  ~Background(void);

  void Create(void) override;
  void Start(void) override {}

  void Render(void) override;

 private:
  std::shared_ptr<Drawables::Bitmap> bg_space_;
};

}  // namespace Intro
}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_INTRO_BACKGROUND_H_
