#include "intro_title_game_object.h"

#include "jass/video.h"

#include "jass/image.h"
#include "jass/texture.h"

namespace GameObjects {

  IntroTitleGameObject::IntroTitleGameObject() {
    this->alpha_title_ = 0;
    this->ticks_title_ = 0;
    this->speed_title_ = 1 * 1000;
  }

  IntroTitleGameObject::~IntroTitleGameObject() {
    bg_intro_.reset();
  }

  void IntroTitleGameObject::Start() {
    this->alpha_title_ = 0;
    this->ticks_title_ = 0;
  }

  void IntroTitleGameObject::Create() {
    std::shared_ptr<Image> image = Image::MakeImage("data/texturi/title.png");
    this->bg_intro_ = Texture::MakeTexture(image);
  }

  void IntroTitleGameObject::Update(const Uint32 dt) {
    this->ticks_title_ += dt;
    this->alpha_title_ = static_cast<float>(ticks_title_) / speed_title_;
    if (alpha_title_ >= 1.0f) this->alpha_title_ = 1.0f;
  }

  void IntroTitleGameObject::Render(Video *const video) {
    // GL_CHECK(glColor4f(1.0f, 1.0f, 1.0f, alpha_title_));
    video->DrawTexture(272, 8, 256, 64, bg_intro_);
  }

}
