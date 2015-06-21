// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_PROJECTILE_H_
#define JASS_SRC_JASS_PROJECTILE_H_
#pragma once

#include "jass/jass.h"

class Proiectile : boost::noncopyable {
public:
  Proiectile(GLfloat xpos, GLfloat ypos, GLfloat angle, GLuint owner);
  void update(const Uint32 dt);
  void getPos(GLfloat& x, GLfloat& y) { x = xpos; y = ypos; };

  bool sterge;
  GLuint owner;
  GLfloat xpos, ypos;

private:
  GLfloat angle;
  Uint32 lifetime;
};

#endif  // JASS_SRC_JASS_PROJECTILE_H_
