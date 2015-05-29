// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_STATE_PLAY_H_
#define JASS_SRC_JASS_STATE_PLAY_H_
#pragma once

#include <vector>

#include "jass/state.h"

#include "jass/jass.h"

static const std::string kStatePlay = "state_play";

class Proiectile;
class Ship;
class Mesh;

class StatePlay : public State {
public:
  StatePlay();
  virtual ~StatePlay();

  void Execute(Uint32 ticks, Uint8* keystate) override;

  void addProiectile(Proiectile* proiectil);

protected:
  void Create() override;
  void Start() override;
  void Stop() override;

private:
  GLuint bgSpace;
  GLuint bgHealthbar;
  GLuint bgBoard;
  std::vector<Proiectile*> proiectile;
  Mesh* ship;
  Ship* nava1;
  Ship* nava2;
};

#endif  // JASS_SRC_JASS_STATE_PLAY_H_
