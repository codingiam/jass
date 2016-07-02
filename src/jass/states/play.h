// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_STATES_PLAY_H_
#define JASS_STATES_PLAY_H_

#include <GL/glew.h>

#include <vector>

#include "jass/states/state.h"

namespace GameObjects {
namespace Play {
class Background;
class Healthbar;
class Ship;
class Board;
class Projectiles;
}  // namespace Play
}  // namespace GameObjects

namespace States {

class Play : public State {
 public:
  Play(void);
  ~Play(void);

  void Update(const double dt, const bool *keys_states) override;
  void Render(void) override;

  void AddProjectile(const GLfloat xpos, const GLfloat ypos,
      const GLfloat angle, const GLuint owner);

 protected:
  void Create(void) override;
  void Start(void) override;
  void Stop(void) override;

 private:
  std::shared_ptr<GameObjects::Play::Background> bg_space_;

  std::shared_ptr<GameObjects::Play::Ship> red_ship_;
  std::shared_ptr<GameObjects::Play::Ship> blue_ship_;

  std::shared_ptr<GameObjects::Play::Healthbar>
      red_ship_healthbar_;
  std::shared_ptr<GameObjects::Play::Healthbar>
      blue_ship_healthbar_;

  std::shared_ptr<GameObjects::Play::Board> bg_board_;

  std::shared_ptr<GameObjects::Play::Projectiles> projectiles_;
};

}  // namespace States

#endif  // JASS_STATES_PLAY_H_
