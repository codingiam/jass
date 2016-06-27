#include "jass/game_objects/intro_menu_game_object.h"

#include "jass/drawables/bitmap_drawable.h"

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
    this->bg_action_ = std::make_shared<Drawables::BitampDrawable>("resources/textures/action.png");
    this->bg_action_->Create();
  }

  void IntroMenuGameObject::Update(const Uint32 dt) {
    this->ticks_action_ += dt;

    this->blue_action_ = static_cast<float>(ticks_action_) / speed_action_;

    if (blue_action_ >= 1.0f) this->ticks_action_ -= speed_action_;
  }

  void IntroMenuGameObject::Render(Video *const video) {
    bg_action_->translation(glm::vec3(262, 440, 0));
    bg_action_->color(glm::vec4(1.0f, 1.0f - blue_action_, blue_action_, 1.0f));
    bg_action_->Render(video);
  }

}
