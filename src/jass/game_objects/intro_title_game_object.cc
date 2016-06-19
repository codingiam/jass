#include "jass/game_objects/intro_title_game_object.h"

#include "jass/drawables/bitmap_drawable.h"

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
    this->bg_intro_ = std::make_shared<Drawables::BitampDrawable>("data/texturi/title.png");
    this->bg_intro_->Create();
  }

  void IntroTitleGameObject::Update(const Uint32 dt) {
    this->ticks_title_ += dt;
    this->alpha_title_ = static_cast<float>(ticks_title_) / speed_title_;
    if (alpha_title_ >= 1.0f) this->alpha_title_ = 1.0f;
  }

  void IntroTitleGameObject::Render(Video *const video) {
    bg_intro_->translation(glm::vec3(272, 8, 0));
    bg_intro_->color(glm::vec4(1.0f, 1.0f, 1.0f, alpha_title_));
    bg_intro_->Render(video);
  }

}
