// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/game_object.h"

namespace GameObjects {
  template <class Base>
  class UpdatableGameObject : public Base {
    static_assert(std::is_base_of<GameObject, Base>::value,
      "Base should be a base of GameObject");
   public:
    virtual void Update(const Uint32 dt) = 0;
    bool Updatable(void) override {
      return true;
    }
  };
}
