// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/projectile.h"

#include <cmath>

Proiectile::Proiectile(GLfloat xpos, GLfloat ypos,
                       GLfloat angle, GLuint owner) {
  this->xpos_ = xpos;
  this->ypos_ = ypos;

  this->angle_ = angle;

  this->owner_ = owner;

  this->sterge_ = false;
}

void Proiectile::Update(const Uint32 dt) {
  Uint32 diff = dt > 25 ? 25 : dt;

  GLfloat amy = -0.5f * cos(static_cast<float>(M_PI) * angle_ / 180);
  GLfloat amx = 0.5f * sin(static_cast<float>(M_PI) * angle_ / 180);

  ypos_ += amy * 0.5f * (diff / 25.0f);
  xpos_ += amx * 0.5f * (diff / 25.0f);

  if (abs(xpos_) >= 6.5f) this->sterge_ = true;
  if (abs(ypos_) >= 5.5f) this->sterge_ = true;
}
