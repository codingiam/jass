// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/projectile.h"

#include <cmath>

Proiectile::Proiectile(GLfloat xpos, GLfloat ypos,
                       GLfloat angle, GLuint owner) {
  this->xpos = xpos;
  this->ypos = ypos;

  this->angle = angle;

  this->owner = owner;

  sterge = false;
}

void Proiectile::update(const Uint32 dt) {
  Uint32 diff = dt > 25 ? 25 : dt;

  GLfloat amy = -0.5f * cos(static_cast<float>(M_PI) * angle / 180);
  GLfloat amx = 0.5f * sin(static_cast<float>(M_PI) * angle / 180);

  ypos += amy * 0.5f * (diff / 25.0f);
  xpos += amx * 0.5f * (diff / 25.0f);

  if (abs(xpos) >= 6.5f) sterge = true;
  if (abs(ypos) >= 5.5f) sterge = true;
}
