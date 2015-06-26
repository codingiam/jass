// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_PROJECTILE_H_
#define JASS_PROJECTILE_H_
#pragma once

#include "jass/jass.h"

class Proiectile : boost::noncopyable {
 public:
  Proiectile(GLfloat xpos, GLfloat ypos, GLfloat angle, GLuint owner);

  void Update(const Uint32 dt);
  void GetPos(GLfloat *x, GLfloat *y) { *x = xpos_; *y = ypos_; }

  bool sterge_;

  GLuint owner_;
  GLfloat xpos_, ypos_;

 private:
  GLfloat angle_;
  Uint32 lifetime_;
};

#endif  // JASS_PROJECTILE_H_
