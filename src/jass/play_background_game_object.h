// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/game_object.h"

class Texture;

namespace GameObjects {

  class PlayBackgroundGameObject : public GameObject {
   public:
    PlayBackgroundGameObject(void);
    ~PlayBackgroundGameObject(void);

    void Create(void) override;
    void Start(void) override {}

    void Render(Video *const video) override;

   private:
    std::shared_ptr<Texture> bg_space_;
  };

}
