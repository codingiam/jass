// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SHIP_H_
#define JASS_SHIP_H_
#pragma once

#include "jass/jass.h"

class Ship : private boost::noncopyable {
 public:
  Ship(GLfloat xpos, GLfloat ypos, Uint32 id, GLfloat angle);

  void Update(const Uint32 dt, const Uint8 *keystate);

  void GetPosition(GLfloat *x, GLfloat *y, GLfloat *angle)
    { *x = xpos_; *y = ypos_; *angle = this->angle_; }

  void SetKeys(Uint32 keys[]);

  bool Collide(GLfloat x, GLfloat y);

  GLfloat GetLife() { return life_; }

 private:
  enum { K_UP = 0, K_DOWN, K_LEFT, K_RIGHT, K_SHOOT, K_SHIELD };

  GLfloat angle_;
  GLfloat xpos_, ypos_;
  GLfloat accel_, speed_;
  GLfloat life_;
  GLfloat energy_;
  GLuint ship_id_;
  Uint32 last_time_ACC_;
  Uint32 last_time_MOV_;
  Uint32 last_time_ROT_;
  Uint32 last_time_SHO_;
  Uint32 keys_[6];
  Uint32 ticks_;
};

#endif  // JASS_SHIP_H_
