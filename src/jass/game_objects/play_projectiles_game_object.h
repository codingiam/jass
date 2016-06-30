// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_PROJECTILE_H_
#define JASS_PROJECTILE_H_
#pragma once

#include <vector>

#include "jass/game_objects/game_object.h"

class Video;

namespace Drawables {
class PrimitivesDrawable;
}

namespace GameObjects {

class PlayShipGameObject;

struct Projectile;

class PlayProjectilesGameObject : public GameObject {
 public:
  PlayProjectilesGameObject(void);
  ~PlayProjectilesGameObject(void);

  void Create(void) override;

  void Update(const Uint32 dt,
      PlayShipGameObject *const red_ship,
      PlayShipGameObject *const blue_ship) override;
  void Render(Video *const video) override;

  void AddProjectile(GLfloat xpos, GLfloat ypos, GLfloat angle, GLuint owner);
  void Clear(void);

 private:
  std::vector<Projectile> projectiles_;
  std::shared_ptr<Drawables::PrimitivesDrawable> points_;
};

}  // namespace GameObjects

#endif  // JASS_PROJECTILE_H_
