// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

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

  void Update(const Uint32 dt) override;
  void Render(Video *const video) override;

 private:
  std::shared_ptr<Drawables::Font> font_;

  Uint32 ticks_intro_text_;
  Uint32 speed_intro_text_;

  float position_text_;

  Uint32 show_to_;

  Uint32 size_intro_text_;
};

}  // namespace Intro
}  // namespace GameObjects
