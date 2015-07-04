#pragma once

#include "jass/game_object.h"

#include "jass/renderable_game_object.h"
#include "jass/updatable_game_object.h"

class Texture;

namespace GameObjects {

  class IntroTextGameObject :
    public UpdatableGameObject<RenderableGameObject<GameObject> > {
   public:
    IntroTextGameObject(void);
    ~IntroTextGameObject(void);

    void Create(void) override;
    void Start(void) override;

    void Update(const Uint32 dt) override;
    void Render(Video *const video) override;

   private:
    Uint32 ticks_intro_text_;
    Uint32 speed_intro_text_;

    float position_text_;

    Uint32 show_to_;

    Uint32 size_intro_text_;
  };

}
