// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_PLAY_PROJECTILES_H_
#define JASS_GAME_OBJECTS_PLAY_PROJECTILES_H_

#include <GL/glew.h>

#include <vector>

#include "jass/game_objects/game_object.h"

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

  void Update(const uint32_t dt,
      Ship *const red_ship,
      Ship *const blue_ship) override;
  void Render(void) override;

  void AddProjectile(GLfloat xpos, GLfloat ypos, GLfloat angle, GLuint owner);
  void Clear(void);

 private:
  std::vector<Projectile> projectiles_;
  std::shared_ptr<Drawables::Primitives> points_;
};

}  // namespace Play
}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_PLAY_PROJECTILES_H_
