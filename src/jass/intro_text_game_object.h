#pragma once

#include "jass/game_object.h"

namespace Drawables {
  class FontDrawable;
}

namespace GameObjects {

  class IntroTextGameObject : public GameObject {
   public:
    IntroTextGameObject(void);
    ~IntroTextGameObject(void);

    void Create(void) override;
    void Start(void) override;

    void Update(const Uint32 dt) override;
    void Render(Video *const video) override;

   private:
    std::shared_ptr<Drawables::FontDrawable> font_;

    Uint32 ticks_intro_text_;
    Uint32 speed_intro_text_;

    float position_text_;

    Uint32 show_to_;

    Uint32 size_intro_text_;
  };

}
