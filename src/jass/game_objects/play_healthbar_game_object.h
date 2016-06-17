// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/game_objects/game_object.h"

namespace Drawables {
  class BitampDrawable;
}

namespace GameObjects {

class PlayHealthbarGameObject : public GameObject {
 public:
  PlayHealthbarGameObject(const int x, const int y, const int w, const int h, std::shared_ptr<GameObject> const &parent);
  ~PlayHealthbarGameObject(void);

  void Create(void) override;
  void Start(void) override;

  void Update(const Uint32 dt) override;
  void Render(Video *const video) override;

 private:
   std::shared_ptr<Drawables::BitampDrawable> bg_healthbar_;

   float life_;

   const int x_, y_, w_, h_;
};

}  // namespace GameObjects
