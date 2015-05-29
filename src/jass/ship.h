// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_SHIP_H_
#define JASS_SRC_JASS_SHIP_H_
#pragma once

#include "jass/jass.h"

class Ship : boost::noncopyable {
public:
  Ship(GLfloat xpos, GLfloat ypos, Uint32 id, GLfloat angle);
  void update(Uint32 ticks, Uint8* keystate);
  void getPosition(GLfloat& x, GLfloat& y, GLfloat& angle) { x = xpos; y = ypos; angle = this->angle; };
  void setkeys(Uint32 keys[]);
  bool colide(GLfloat x, GLfloat y);
  GLfloat getLife() { return life; };

private:
  enum { K_UP = 0, K_DOWN, K_LEFT, K_RIGHT, K_SHOOT, K_SHIELD };

  GLfloat angle;
  GLfloat xpos, ypos;
  GLfloat accel, speed;
  GLfloat life;
  GLfloat energy;
  GLuint shipId;
  Uint32 lastTimeACC;
  Uint32 lastTimeMOV;
  Uint32 lastTimeROT;
  Uint32 lastTimeSHO;
  Uint32 keys[6];
};

#endif  // JASS_SRC_JASS_SHIP_H_
