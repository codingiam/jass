// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/projectile.h"

#include <cmath>

Proiectile::Proiectile( GLfloat xpos, GLfloat ypos, GLfloat angle, GLuint owner ) {
  this->xpos = xpos;
  this->ypos = ypos;

  this->angle = angle;

  this->owner = owner;

  lastUpdate = 0;
  sterge = false;
}

void Proiectile::update(Uint32 ticks) {
  if (!lastUpdate) lastUpdate = ticks;

  Uint32 diff = ticks - lastUpdate;
  if (diff > 25) diff = 25;
  
  GLfloat amy = -0.5f * cos( 3.1415f * angle / 180 );
  GLfloat amx = 0.5f * sin( 3.1415f * angle / 180 );
  
  ypos += amy * 0.5f * (diff / 25);
  xpos += amx * 0.5f * (diff / 25);

  if (diff > 25) {
    lastUpdate = ticks;
  }

  if (abs(xpos) >= 6.0f) sterge = true;
  if (abs(ypos) >= 5.0f) sterge = true;
}
