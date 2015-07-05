// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/play_projectile_game_object.h"

#include <cmath>

namespace GameObjects {

  PlayProjectileGameObject::PlayProjectileGameObject(GLfloat xpos, GLfloat ypos,
    GLfloat angle, GLuint owner) {
      this->xpos_ = xpos;
      this->ypos_ = ypos;

      this->angle_ = angle;

      this->owner_ = owner;
  }

  PlayProjectileGameObject::~PlayProjectileGameObject() {
  }

  void PlayProjectileGameObject::Update(const Uint32 dt) {
    Uint32 diff = dt > 25 ? 25 : dt;

    GLfloat amy = -0.5f * cos(static_cast<float>(M_PI) * angle_ / 180);
    GLfloat amx = 0.5f * sin(static_cast<float>(M_PI) * angle_ / 180);

    ypos_ += amy * 0.5f * (diff / 25.0f);
    xpos_ += amx * 0.5f * (diff / 25.0f);
  }

  void PlayProjectileGameObject::Render(Video *const video) {
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -10.f);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glPointSize(5.0f);

    glBegin(GL_POINTS);

    if (owner_ == 1) {
      glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    } else {
      glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    }
    glVertex3f(xpos_, ypos_, 0);

    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
  }

}
