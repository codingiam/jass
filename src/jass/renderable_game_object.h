// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/game_object.h"

class Video;

namespace GameObjects {
  template <class Base>
  class RenderableGameObject : public Base {
    static_assert(std::is_base_of<GameObject, Base>::value,
      "Base should be a base of GameObject");
   public:
    virtual void Render(Video *const video) = 0;
    bool Renderable(void) override {
      return true;
    }
  };
}
