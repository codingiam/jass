#pragma once

#include "jass/game_object.h"

#include "jass/renderable_game_object.h"
#include "jass/updatable_game_object.h"

class Texture;

namespace GameObjects {

  class IntroTitleGameObject :
    public UpdatableGameObject<RenderableGameObject<GameObject> > {
   public:
    IntroTitleGameObject(void);
    ~IntroTitleGameObject(void);

    void Create(void) override;
    void Start(void) override;

    void Update(const Uint32 dt) override;
    void Render(Video *const video) override;

   private:
    std::shared_ptr<Texture> bg_intro_;

    float alpha_title_;
    Uint32 ticks_title_;
    Uint32 speed_title_;
  };

}
