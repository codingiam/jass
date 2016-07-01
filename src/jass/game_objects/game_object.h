// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/jass.h"

class Video;

namespace GameObjects {

namespace Play {
class Ship;
}

class GameObject {
 public:
  GameObject(const GameObject &) = delete;
  GameObject & operator=(const GameObject &) = delete;

  GameObject(void);
  explicit GameObject(std::shared_ptr<GameObject> const &parent);
  virtual ~GameObject(void);

  virtual void Create(void) { }
  virtual void Start(void) { }

  virtual void Update(const Uint32 dt,
      Play::Ship *const red_ship,
      Play::Ship *const blue_ship) {}
  virtual void Update(const Uint32 dt, const Uint8 *keystate) { }
  virtual void Update(const Uint32 dt) { }
  virtual void Render(Video *const video) { }

//  virtual bool Updatable(void) { return false; }
//  virtual bool Renderable(void)  { return false; }

 protected:
  std::weak_ptr<GameObject> const parent_;
};

}  // namespace GameObjects
