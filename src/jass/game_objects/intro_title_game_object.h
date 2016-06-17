#pragma once

#include "jass/game_objects/game_object.h"

namespace Drawables {
  class BitampDrawable;
}

namespace GameObjects {

  class IntroTitleGameObject : public GameObject {
   public:
    IntroTitleGameObject(void);
    ~IntroTitleGameObject(void);

    void Create(void) override;
    void Start(void) override;

    void Update(const Uint32 dt) override;
    void Render(Video *const video) override;

   private:
    std::shared_ptr<Drawables::BitampDrawable> bg_intro_;

    float alpha_title_;
    Uint32 ticks_title_;
    Uint32 speed_title_;
  };

}
