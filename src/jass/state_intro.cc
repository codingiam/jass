// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/state_intro.h"

#include "jass/video.h"
#include "jass/application.h"
#include "jass/states_manager.h"
#include "jass/window.h"
#include "jass/image.h"
#include "jass/texture.h"

static const char * introText[] = {
  "  Acest joc este proiectul nostru pentru cursul de grafica.\0",
  "Sper ca va v-a face placere sa-l jucati si bineintles sa ne\0",
  "dati o nota pe masura efortului.\0",
  "  Scopul jocului este sa scapati cu nava intacta din batalie.\0",
  " \0",
  "  Si acuma urmeaza tastele:\0",
  " \0"
};

StateIntro::StateIntro() {
  this->bg_space_ = 0;
  this->bg_intro_ = 0;
  this->bg_action_ = 0;

  this->ticks_title_ = 0;
  this->ticks_action_ = 0;
  this->ticks_intro_text_ = 0;

  this->speed_title_ = 1 * 1000;
  this->speed_action_ = 2 * 1000;
  this->speed_intro_text_ = 10 * 1000;

  this->size_intro_text_ = 0;

  for (int i = 0; i < 7; i++) {
    this->size_intro_text_ += strlen(introText[i]);  // introText[i].length();
  }
}

StateIntro::~StateIntro() {
  bg_space_.reset();
  bg_intro_.reset();
  bg_action_.reset();
}

void StateIntro::Create() {
  boost::shared_ptr<Image> image = Image::MakeImage("data/texturi/introbg.png");
  this->bg_space_ = Texture::MakeTexture(image);

  image = Image::MakeImage("data/texturi/title.png");
  this->bg_intro_ = Texture::MakeTexture(image);

  image = Image::MakeImage("data/texturi/action.png");
  this->bg_action_ = Texture::MakeTexture(image);

  if (!(bg_space_) || !(bg_intro_) || !(bg_action_)) {
    throw std::runtime_error("Could not create textures for 'stateintro'");
  }
}

void StateIntro::Start() {
  this->ticks_title_ = 0;
  this->ticks_action_ = 0;
  this->ticks_intro_text_ = 0;
}

void StateIntro::Stop() {
}

void StateIntro::Update(const Uint32 dt, const Uint8 *keystate) {
  ticks_title_ += dt;
  ticks_action_ += dt;
  ticks_intro_text_ += dt;

  this->alpha_title_ = static_cast<float>(ticks_title_) / speed_title_;
  this->blue_action_ = static_cast<float>(ticks_action_) / speed_action_;
  this->position_text_ =
    static_cast<float>(ticks_intro_text_) / speed_intro_text_;

  if (alpha_title_ >= 1.0f) this->alpha_title_ = 1.0f;
  if (blue_action_ >= 1.0f) this->ticks_action_ -= speed_action_;
  if (position_text_ >= 1.0f) this->position_text_ = 1.0f;

  this->show_to_ = (Uint32) (size_intro_text_ * position_text_);

  if (keystate[SDL_SCANCODE_SPACE])
      State::SetState(State::Find(kStatePlay).lock().get());

  if (keystate[SDL_SCANCODE_F10])
      State::SetState(NULL);
}

void StateIntro::Render(Video *const video) {
  glClear(GL_COLOR_BUFFER_BIT);
  video->Init2DScene(Window::kWidth, Window::kHeight);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  video->DrawTexture(0, 0, Window::kWidth, Window::kHeight, bg_space_);

  glColor4f(1.0f, 1.0f, 1.0f, alpha_title_);
  video->DrawTexture(272, 8, 256, 64, bg_intro_);

  glColor4f(1.0f, 1.0f - blue_action_, blue_action_, 1.0f);
  video->DrawTexture(262, 440, 276, 64, bg_action_);

  glColor3f(1.0f, 1.0f, 1.0f);

  Uint32 marime = 0;
  char buffer[100 + 1];

  for (int i = 0; show_to_ > 0; i++) {
    marime = strlen(introText[i]);  // introText[i].length();
    if (marime > show_to_) marime = show_to_;
    if (marime > 100) marime = 100;
    // size_t copied = introText[i].copy(buffer, marime);
    strncpy(buffer, introText[i], marime);
    buffer[marime] = '\0';
    show_to_ -= marime;
    video->Print(90, 105 + 20 * i, buffer);
  }
}
