// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_PLAY_SHIP_H_
#define JASS_GAME_OBJECTS_PLAY_SHIP_H_

#include <glad/glad.h>

#include <array>

#include "jass/game_objects/game_object.h"

namespace Drawables {
class Geometry;
}

namespace GameObjects {
namespace Play {

class Ship : public GameObject {
 public:
  Ship(const GLfloat xpos, const GLfloat ypos, const uint32_t id,
      const GLfloat angle, std::array<int, 6> const &keys);
  ~Ship(void);

  void Create(void) override;
  void Start(void) override;

  void Render(void) override;

  bool Collide(const GLfloat x, const GLfloat y);
  GLfloat GetLife(void);

  void Update(const double dt, const bool *keys_states) override;

 private:
  std::shared_ptr<Drawables::Geometry> ship_;

  const GLfloat ixpos_, iypos_;
  const uint32_t id_;
  const GLfloat iangle_;

  const std::array<int, 6> keys_;

  enum { K_UP = 0, K_DOWN, K_LEFT, K_RIGHT, K_SHOOT/*, K_SHIELD*/ };

  GLfloat angle_;
  GLfloat xpos_, ypos_;
  GLfloat accel_;
  GLfloat life_;
  GLfloat energy_;

  double last_time_ACC_;
  double last_time_MOV_;
  double last_time_ROT_;
  double last_time_SHO_;

  double ticks_;
};

}  // namespace Play
}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_PLAY_SHIP_H_
