// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_PROJECTILE_H_
#define JASS_PROJECTILE_H_
#pragma once

#include <vector>

#include "jass/game_objects/game_object.h"

class Video;

namespace Drawables {
class Primitives;
}

namespace GameObjects {
namespace Play {

class Ship;

struct Projectile;

class Projectiles : public GameObject {
 public:
  Projectiles(void);
  ~Projectiles(void);

  void Create(void) override;

  void Update(const Uint32 dt,
      Ship *const red_ship,
      Ship *const blue_ship) override;
  void Render(Video *const video) override;

  void AddProjectile(GLfloat xpos, GLfloat ypos, GLfloat angle, GLuint owner);
  void Clear(void);

 private:
  std::vector<Projectile> projectiles_;
  std::shared_ptr<Drawables::Primitives> points_;
};

}  // namespace Play
}  // namespace GameObjects

#endif  // JASS_PROJECTILE_H_
