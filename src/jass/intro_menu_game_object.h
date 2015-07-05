#pragma once

#include "jass/game_object.h"

class Texture;

namespace GameObjects {

  class IntroMenuGameObject : public GameObject {
   public:
    IntroMenuGameObject(void);
    ~IntroMenuGameObject(void);

    void Create(void) override;
    void Start(void) override;

    void Update(const Uint32 dt) override;
    void Render(Video *const video) override;

   private:
    std::shared_ptr<Texture> bg_action_;

    Uint32 ticks_action_;

    Uint32 speed_action_;

    float blue_action_;
  };

}
