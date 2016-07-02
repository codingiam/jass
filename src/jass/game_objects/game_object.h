// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_GAME_OBJECT_H_
#define JASS_GAME_OBJECTS_GAME_OBJECT_H_

#include <memory>

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

  virtual void Update(const uint32_t dt,
      Play::Ship *const red_ship,
      Play::Ship *const blue_ship) {}
  virtual void Update(const uint32_t dt, const uint8_t *keystate) { }
  virtual void Update(const uint32_t dt) { }
  virtual void Render(void) { }

//  virtual bool Updatable(void) { return false; }
//  virtual bool Renderable(void)  { return false; }

 protected:
  std::weak_ptr<GameObject> const parent_;
};

}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_GAME_OBJECT_H_
