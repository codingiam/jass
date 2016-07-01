// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

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

  void Update(const Uint32 dt) override;
  void Render(Video *const video) override;

 private:
  std::shared_ptr<Drawables::Bitmap> bg_action_;

  Uint32 ticks_action_;

  Uint32 speed_action_;

  float blue_action_;
};

}  // namespace Intro
}  // namespace GameObjects
