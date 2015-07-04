#include "intro_menu_game_object.h"

#include "jass/video.h"

#include "jass/image.h"
#include "jass/texture.h"

namespace GameObjects {

  IntroMenuGameObject::IntroMenuGameObject() {
    this->ticks_action_ = 0;
    this->speed_action_ = 2 * 1000;
  }

  IntroMenuGameObject::~IntroMenuGameObject() {
  }

  void IntroMenuGameObject::Start() {
    this->ticks_action_ = 0;
  }

  void IntroMenuGameObject::Create() {
    std::shared_ptr<Image> image = Image::MakeImage("data/texturi/action.png");
    this->bg_action_ = Texture::MakeTexture(image);
  }

  void IntroMenuGameObject::Update(const Uint32 dt) {
    this->ticks_action_ += dt;

    this->blue_action_ = static_cast<float>(ticks_action_) / speed_action_;

    if (blue_action_ >= 1.0f) this->ticks_action_ -= speed_action_;
  }

  void IntroMenuGameObject::Render(Video *const video) {
    glColor4f(1.0f, 1.0f - blue_action_, blue_action_, 1.0f);
    video->DrawTexture(262, 440, 276, 64, bg_action_);
  }

}
