// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_PROJECTILE_H_
#define JASS_PROJECTILE_H_
#pragma once

#include "jass/game_objects/game_object.h"

class Video;

namespace GameObjects {

  class PlayProjectileGameObject : public GameObject {
  public:
    PlayProjectileGameObject(GLfloat xpos, GLfloat ypos, GLfloat angle, GLuint owner);
    ~PlayProjectileGameObject(void);

    void Update(const Uint32 dt);
    void Render(Video *const video);

    // void GetPos(GLfloat *x, GLfloat *y) { *x = xpos_; *y = ypos_; }

    GLuint owner_;
    GLfloat xpos_, ypos_;

  private:
    GLfloat angle_;
  };

}

#endif  // JASS_PROJECTILE_H_
