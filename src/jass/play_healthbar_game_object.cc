#include "play_healthbar_game_object.h"

#include "jass/video.h"

#include "jass/image.h"
#include "jass/texture.h"

#include "jass/game_object.h"

#include "jass/play_ship_game_object.h"

namespace GameObjects {

  PlayHealthbarGameObject::PlayHealthbarGameObject(const int x, const int y, const int w, const int h,
    std::shared_ptr<GameObject> const &parent) : GameObject(parent), x_(x), y_(y), w_(w), h_(h)
  {
    this->life_ = 0;
  }

  PlayHealthbarGameObject::~PlayHealthbarGameObject() {
  }

  void PlayHealthbarGameObject::Create() {
    std::shared_ptr<Image> image = Image::MakeImage("data/texturi/healthbar.png");
    this->bg_healthbar_ = Texture::MakeTexture(image);
  }

  void PlayHealthbarGameObject::Start() {
  }

  void PlayHealthbarGameObject::Update(const Uint32 dt) {
    this->life_ = std::static_pointer_cast<PlayShipGameObject>(parent_.lock())->GetLife();
  }

  void PlayHealthbarGameObject::Render(Video *const video) {
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    video->DrawTexture(x_, y_, w_, h_, bg_healthbar_, 1.0f - life_);
  }

}
