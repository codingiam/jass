// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <array>

#include "jass/game_objects/game_object.h"

namespace Drawables {
class Geometry;
}

namespace GameObjects {
namespace Play {

class Ship : public GameObject {
 public:
  Ship(const GLfloat xpos, const GLfloat ypos, const Uint32 id,
      const GLfloat angle, std::array<Uint32, 6> const &keys);
  ~Ship(void);

  void Create(void) override;
  void Start(void) override;

  void Render(Video *const video) override;

  bool Collide(const GLfloat x, const GLfloat y);
  GLfloat GetLife(void);

  void Update(const Uint32 dt, const Uint8 *keystate) override;

 private:
  std::shared_ptr<Drawables::Geometry> ship_;

  const GLfloat ixpos_, iypos_;
  const Uint32 id_;
  const GLfloat iangle_;

  const std::array<Uint32, 6> keys_;

  enum { K_UP = 0, K_DOWN, K_LEFT, K_RIGHT, K_SHOOT, K_SHIELD };

  GLfloat angle_;
  GLfloat xpos_, ypos_;
  GLfloat accel_;
  GLfloat life_;
  GLfloat energy_;
  Uint32 last_time_ACC_;
  Uint32 last_time_MOV_;
  Uint32 last_time_ROT_;
  Uint32 last_time_SHO_;
  Uint32 ticks_;
};

}  // namespace Play
}  // namespace GameObjects
