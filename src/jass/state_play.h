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
class Texture;

class StatePlay : public State {
 public:
  StatePlay(void);
  ~StatePlay(void);

  void Execute(const Uint32 dt, const Uint8 *keystate) override;
  void Render(Video *const video) override;

  void AddProjectile(Proiectile *projectile);

 protected:
  void Create(void) override;
  void Start(void) override;
  void Stop(void) override;

 private:
  boost::shared_ptr<Texture> bg_space_;
  boost::shared_ptr<Texture> bg_healthbar_;
  boost::shared_ptr<Texture> bg_board_;

  std::vector<Proiectile*> projectiles_;

  Mesh* ship_;

  Ship* nava1_;
  Ship* nava2_;
};

#endif  // JASS_STATE_PLAY_H_
