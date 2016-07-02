// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GAME_OBJECTS_PLAY_HEALTHBAR_H_
#define JASS_GAME_OBJECTS_PLAY_HEALTHBAR_H_

#include "jass/game_objects/game_object.h"

namespace Drawables {
class Bitmap;
}

namespace GameObjects {
namespace Play {

class Healthbar : public GameObject {
 public:
  Healthbar(const int x, const int y, const int w, const int h,
      std::shared_ptr<GameObject> const &parent);
  ~Healthbar(void);

  void Create(void) override;
  void Start(void) override;

  void Update(const uint32_t dt) override;
  void Render(void) override;

 private:
  std::shared_ptr<Drawables::Bitmap> bg_healthbar_;

  float life_;

  const int x_, y_, w_, h_;
};

}  // namespace Play
}  // namespace GameObjects

#endif  // JASS_GAME_OBJECTS_PLAY_HEALTHBAR_H_
