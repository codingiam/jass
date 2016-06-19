#include "jass/game_objects/intro_text_game_object.h"

#include "jass/video.h"

#include "jass/image.h"
#include "jass/texture.h"

#include "jass/drawables/font_drawable.h"

#include <array>

namespace {
  const std::array<const char *, 10> introText = {
    "  Acest joc este proiectul nostru pentru",
    "cursul de grafica.",
    "  Sper ca va v-a face placere sa-l jucati si",
    "bineintles sa ne dati o nota pe masura",
    "efortului.",
    "  Scopul jocului este sa scapati cu nava",
    "intacta din batalie.",
    " ",
    "  Si acuma urmeaza tastele:",
    " "
  };
}

namespace GameObjects {

  IntroTextGameObject::IntroTextGameObject() {
    this->ticks_intro_text_ = 0;

    this->speed_intro_text_ = 10 * 1000;

    this->size_intro_text_ = 0;

    for (int i = 0; i < 10; i++) {
      this->size_intro_text_ += strlen(introText[i]);  // introText[i].length();
    }
  }

  IntroTextGameObject::~IntroTextGameObject() {
  }

  void IntroTextGameObject::Start() {
    this->ticks_intro_text_ = 0;
  }

  void IntroTextGameObject::Create() {
    this->font_ = std::make_shared<Drawables::FontDrawable>("data/fonturi/font.png");
    this->font_->Create();
  }

  void IntroTextGameObject::Update(const Uint32 dt) {
    this->ticks_intro_text_ += dt;

    this->position_text_ =
      static_cast<float>(ticks_intro_text_) / speed_intro_text_;

    if (position_text_ >= 1.0f) this->position_text_ = 1.0f;

    this->show_to_ = (Uint32) (size_intro_text_ * position_text_);
  }

  void IntroTextGameObject::Render(Video *const video) {
    // GL_CHECK(glColor3f(1.0f, 1.0f, 1.0f));

    Uint32 marime = 0;
    char buffer[100 + 1];

    for (int i = 0; show_to_ > 0; i++) {
      marime = (Uint32) strlen(introText[i]);  // introText[i].length();
      if (marime > show_to_) marime = show_to_;
      if (marime > 100) marime = 100;
      // size_t copied = introText[i].copy(buffer, marime);
      strncpy(buffer, introText[i], marime);
      buffer[marime] = '\0';
      show_to_ -= marime;
      font_->translation(glm::vec3(40, 105 + 20 * i, 0));
      font_->scale(glm::vec3(800.0 / 800.0, 600.0 / 600.0, 1.0));
      font_->text(buffer);
      font_->Render(video);
    }
  }

}
