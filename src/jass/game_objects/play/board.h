// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_PLAY_BOARD_H_
#define JASS_GAME_OBJECTS_PLAY_BOARD_H_

#include "jass/game_objects/game_object.h"

namespace Drawables {
class Bitmap;
}

namespace GameObjects {
namespace Play {

class Board : public GameObject {
 public:
  Board(void);
  ~Board(void);

  void Create(void) override;
  void Start(void) override {}

  void Render(void) override;

 private:
  std::shared_ptr<Drawables::Bitmap> bg_board_;
};

}  // namespace Play
}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_PLAY_BOARD_H_
