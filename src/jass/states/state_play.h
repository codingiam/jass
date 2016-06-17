// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATE_PLAY_H_
#define JASS_STATE_PLAY_H_
#pragma once

#include <vector>

#include "jass/states/state.h"

#include "jass/jass.h"

namespace GameObjects {
  class PlayBackgroundGameObject;
  class PlayHealthbarGameObject;
  class PlayShipGameObject;
  class PlayBoardGameObject;
  class PlayProjectileGameObject;
}

namespace States {

class StatePlay : public State {
 public:
  StatePlay(void);
  ~StatePlay(void);

  void Update(const Uint32 dt, const Uint8 *keystate) override;
  void Render(Video *const video) override;

  void AddProjectile(const GLfloat xpos, const GLfloat ypos, const GLfloat angle, const GLuint owner);

 protected:
  void Create(void) override;
  void Start(void) override;
  void Stop(void) override;

 private:
  std::shared_ptr<GameObjects::PlayBackgroundGameObject> bg_space_;

  std::shared_ptr<GameObjects::PlayShipGameObject> red_ship_;
  std::shared_ptr<GameObjects::PlayShipGameObject> blue_ship_;

  std::shared_ptr<GameObjects::PlayHealthbarGameObject> red_ship_healthbar_;
  std::shared_ptr<GameObjects::PlayHealthbarGameObject> blue_ship_healthbar_;
  
  std::shared_ptr<GameObjects::PlayBoardGameObject> bg_board_;

  std::vector<std::shared_ptr<GameObjects::PlayProjectileGameObject> > projectiles_;
};

}

#endif  // JASS_STATE_PLAY_H_
