#pragma once

#include "jass/game_objects/game_object.h"

class Texture;

namespace GameObjects {

  class PlayHealthbarGameObject : public GameObject {
   public:
    PlayHealthbarGameObject(const int x, const int y, const int w, const int h, std::shared_ptr<GameObject> const &parent);
    ~PlayHealthbarGameObject(void);

    void Create(void) override;
    void Start(void) override;

    void Update(const Uint32 dt) override;
    void Render(Video *const video) override;

   private:
     std::shared_ptr<Texture> bg_healthbar_;

     float life_;
     
     const int x_, y_, w_, h_;
  };

}
