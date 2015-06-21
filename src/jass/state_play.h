// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATE_PLAY_H_
#define JASS_STATE_PLAY_H_
#pragma once

#include <vector>

#include "jass/state.h"

#include "jass/jass.h"

class Proiectile;
class Ship;
class Mesh;

class StatePlay : public State {
 public:
  StatePlay(void);
  virtual ~StatePlay(void);

  void Execute(const Uint32 dt, const Uint8 *keystate) override;
  void Render(Video *const video) override;

  void addProiectile(Proiectile* proiectil);

 protected:
  void Create(void) override;
  void Start(void) override;
  void Stop(void) override;

 private:
  GLuint bgSpace;
  GLuint bgHealthbar;
  GLuint bgBoard;
  std::vector<Proiectile*> proiectile;
  Mesh* ship;
  Ship* nava1;
  Ship* nava2;
};

#endif  // JASS_STATE_PLAY_H_
