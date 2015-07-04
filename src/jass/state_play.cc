// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/state_play.h"

#include <cstdio>
#include <vector>

#include "jass/video.h"
#include "jass/application.h"
#include "jass/mesh.h"
#include "jass/ship.h"
#include "jass/states_manager.h"
#include "jass/projectile.h"
#include "jass/window.h"
#include "jass/image.h"
#include "jass/texture.h"

StatePlay::StatePlay() {
  this->bg_space_ = 0;
  this->bg_healthbar_ = 0;
  this->bg_board_ = 0;

  this->ship_ = new Mesh();

  this->nava1_ = NULL;
  this->nava2_ = NULL;
}

StatePlay::~StatePlay() {
  delete ship_;

  delete nava1_;
  delete nava2_;

  bg_space_.reset();
  bg_healthbar_.reset();
  bg_board_.reset();

  for (unsigned int i = 0; i < projectiles_.size(); i++) {
    Proiectile* p = projectiles_[i];
    delete p;
  }
}

void StatePlay::Create() {
  ship_->LoadMeshObj("spaceship.obj", "data/obiecte/");

  std::shared_ptr<Image> image = Image::MakeImage("data/texturi/spacebg.png");
  this->bg_space_ = Texture::MakeTexture(image);

  image = Image::MakeImage("data/texturi/healthbar.png");
  this->bg_healthbar_ = Texture::MakeTexture(image);

  image = Image::MakeImage("data/texturi/board.png");
  this->bg_board_ = Texture::MakeTexture(image);
}

void StatePlay::Start() {
  this->nava1_ = new Ship(-4.5f, 3.25f, 1, 0.0f);
  this->nava2_ = new Ship(4.5f, -2.40f, 2, 180.0f);

  Uint32 keys1[] = { SDL_SCANCODE_Q, SDL_SCANCODE_S, SDL_SCANCODE_C,
    SDL_SCANCODE_V, SDL_SCANCODE_LCTRL, 0 };
  nava1_->SetKeys(keys1);

  Uint32 keys2[] = { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL, 0 };
  nava2_->SetKeys(keys2);
}

void StatePlay::Stop() {
  delete nava1_; this->nava1_ = NULL;
  delete nava2_; this->nava2_ = NULL;
}

void StatePlay::Update(const Uint32 dt, const Uint8 *keystate) {
  for (unsigned int i = 0; i < projectiles_.size(); i++) {
    Proiectile* p = projectiles_[i];
    p->Update(dt);

    Ship* tmp = (p->owner_ == 1) ? (nava2_) : (nava1_);
    if (tmp->Collide(p->xpos_, p->ypos_)) p->sterge_ = true;
  }

  std::vector<Proiectile*>::iterator it;
  if ((it = projectiles_.begin()) != projectiles_.end()) {
    do {
      if ((*it)->sterge_) {
        delete (*it);
                it = projectiles_.erase(it);
      } else {
        it++;
      }
    } while (it != projectiles_.end());
  }

  nava1_->Update(dt, keystate);
  nava2_->Update(dt, keystate);

  if (keystate[SDL_SCANCODE_ESCAPE])
      State::SetState(State::Find(kStateIntro).lock().get());

  if ((nava1_->GetLife() <= 0.0f) || (nava2_->GetLife() <= 0.0f))
      State::SetState(State::Find(kStateIntro).lock().get());
}

void StatePlay::AddProjectile(Proiectile *projectile) {
  projectiles_.push_back(projectile);
}

void StatePlay::Render(Video *const video) {
  glClear(GL_COLOR_BUFFER_BIT);
  video->Init2DScene(Window::kWidth, Window::kHeight);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  video->DrawTexture(0, 0, Window::kWidth, Window::kHeight, bg_space_);

  video->Init3DScene(Window::kWidth, Window::kHeight);

  glPushMatrix();

  GLfloat x = .0f, y = .0f, angle = .0f;
  nava1_->GetPosition(&x, &y, &angle);

  glTranslatef(x, y, -10.0f);
  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glScalef(0.035f, 0.035f, 0.035f);
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  ship_->Display();

  glPopMatrix();
  glPushMatrix();

  nava2_->GetPosition(&x, &y, &angle);

  glTranslatef(x, y, -10.0f);
  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glScalef(0.035f, 0.035f, 0.035f);
  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
  ship_->Display();

  glPopMatrix();

  glTranslatef(0.0f, 0.0f, -10.f);

  glDisable(GL_TEXTURE_2D); glDisable(GL_LIGHTING);
    glPointSize(5.0f);
  glBegin(GL_POINTS);
  for (unsigned int i = 0; i < projectiles_.size(); i++) {
    Proiectile* p = projectiles_[i];
    p->GetPos(&x, &y);

    if (p->owner_ == 1) {
      glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    } else {
      glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    }
    glVertex3f(x, y, 0);
  }
  glEnd();

  glEnable(GL_LIGHTING); glEnable(GL_TEXTURE_2D);

  video->Init2DScene(Window::kWidth, Window::kHeight);

  float life = nava1_->GetLife();
  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
  video->DrawTexture(10, 10, 20, 512, bg_healthbar_, 1.0f - life);

  life = nava2_->GetLife();
  video->DrawTexture(770, 10, 20, 512, bg_healthbar_, 1.0f - life);

  video->DrawTexture(10, 530, 780, 64, bg_board_);
}
