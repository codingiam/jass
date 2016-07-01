// Copyright (c) 2016, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/play/ship.h"

#include "jass/subsystems/video.h"

#include "jass/drawables/geometry.h"

#include "jass/states/states_manager.h"
#include "jass/states/play.h"

namespace {
  int pnpoly(int npol, float *xp, float *yp, float x, float y) {
    int i, j, c = 0;
    for (i = 0, j = npol-1; i < npol; j = i++) {
      if ((((yp[i] <= y) && (y < yp[j])) ||
        ((yp[j] <= y) && (y < yp[i]))) &&
        (x < (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
        c = !c;
    }
    return c;
  }
}  // namespace

namespace GameObjects {
namespace Play {

Ship::Ship(const GLfloat xpos, const GLfloat ypos,
    const Uint32 id, const GLfloat angle, std::array<Uint32, 6> const &keys) :
  ixpos_(xpos), iypos_(ypos), id_(id), iangle_(angle), keys_(keys) {
}

Ship::~Ship() {
  ship_.reset();
}

void Ship::Create() {
  this->ship_ = std::make_shared<Drawables::Geometry>(
      "resources/objects/spaceship.obj");
  this->ship_->Create();
}

void Ship::Start() {
  this->xpos_ = ixpos_;
  this->ypos_ = iypos_;
  this->angle_ = iangle_;

  this->accel_ = 0.0f;
  this->life_ = 1.0f;
  this->energy_ = 1.0f;

  this->last_time_ACC_ = 0;
  this->last_time_MOV_ = 0;
  this->last_time_ROT_ = 0;
  this->last_time_SHO_ = 0;

  this->ticks_ = 0;
}

void Ship::Update(const Uint32 dt, const Uint8 *keystate) {
  ticks_ += dt;

  if ((ticks_ - last_time_ACC_) > 150) {
    if (keystate[keys_[K_UP]]) {
      accel_ += 0.055f;
      if (accel_ > 1.0f) this->accel_ = 1.0f;
    }

    if (keystate[keys_[K_DOWN]]) {
      accel_ -= 0.055f;
      if (accel_ < -1.0f) this->accel_ = -1.0f;
    }

    if (accel_ < 0) {
      accel_ += 0.025f;
      if (accel_ > 0.0f) this->accel_ = 0.0f;
    }

    if (accel_ > 0) {
      accel_ -= 0.025f;
      if (accel_ < 0.0f) this->accel_ = 0.0f;
    }

    this->last_time_ACC_ = ticks_;
  }

  if ((ticks_ - last_time_ROT_) > 100) {
    if (keystate[keys_[K_LEFT]]) {
      angle_ += 10.0f;
    }

    if (keystate[keys_[K_RIGHT]]) {
      angle_ -= 10.0f;
    }

    if (angle_ > 360.0f) angle_ -= 360.0f;
    if (angle_ < 0.0f) angle_ += 360.0f;

    this->last_time_ROT_ = ticks_;
  }

  if ((ticks_ - last_time_SHO_) > 100) {
    if ((keystate[keys_[K_SHOOT]]) && (energy_ >= 0.15f)) {
      std::shared_ptr<States::Play> play =
        std::static_pointer_cast<States::Play>(
            States::State::Find(States::kPlay).lock());

      GLfloat amy = - cos(3.141516f * angle_ / 180);
      GLfloat amx = sin(3.141516f * angle_ / 180);

      play->AddProjectile(xpos_ + amx, ypos_ + amy, angle_, id_);

      energy_ -= 0.15f;

      this->last_time_SHO_ = ticks_;
    }

    energy_ += 0.01f;
    if (energy_ > 1.0f) this->energy_ = 1.0f;
  }

  Uint32 diff = ticks_ - last_time_MOV_;

  if (diff > 100) diff = 100;

  GLfloat amy = - cos(3.141516f * angle_ / 180);
  GLfloat amx = sin(3.141516f * angle_ / 180);

  ypos_ += accel_ * 0.25f * (diff / 100.f) * amy;
  xpos_ += accel_ * 0.25f * (diff / 100.f) * amx;

  if (xpos_ <= -5.8f) this->xpos_ = 5.75f;
  if (xpos_ >= 5.8f) this->xpos_ = -5.75f;

  if (ypos_ <= -4.5f) this->ypos_ = 4.45f;
  if (ypos_ >= 4.5f) this->ypos_ = -4.45f;

  if (diff > 100) {
    this->last_time_MOV_ = ticks_;
  }
}

void Ship::Render(Video *const video) {
  ship_->translation(glm::vec3(xpos_, ypos_, -10.0f));
  ship_->rotation(glm::rotate(glm::angleAxis(glm::radians(90.0f),
      glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(angle_),
      glm::vec3(0.0f, 1.0f, 0.0f)));
  ship_->scale(glm::vec3(0.035f, 0.035f, 0.035f));

  if (id_ == 1) {
    ship_->color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  } else {
    ship_->color(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
  }

  ship_->Render(video);
}

bool Ship::Collide(const GLfloat x, const GLfloat y) {
  GLfloat ams = sin(3.141516f * angle_ / 180);
  GLfloat amc = cos(3.141516f * angle_ / 180);

  GLfloat xp[4], yp[4];

  xp[0] = xpos_ + (-0.40f) * amc - (0.55f) * ams;
  yp[0] = ypos_ + (-0.40f) * ams + (0.55f) * amc;

  xp[1] = xpos_ + (0.40f) * amc - (0.55f) * ams;
  yp[1] = ypos_ + (0.40f) * ams + (0.55f) * amc;

  xp[2] = xpos_ + (0.40f) * amc - (-0.55f) * ams;
  yp[2] = ypos_ + (0.40f) * ams + (-0.55f) * amc;

  xp[3] = xpos_ + (-0.40f) * amc - (-0.55f) * ams;
  yp[3] = ypos_ + (-0.40f) * ams + (-0.55f) * amc;


  bool hit = (pnpoly(4, xp, yp, x, y) == 1);
  if (hit) {
    life_ -= 0.10f;
    // std::cout << life << std::endl;
  }

  return hit;
}

GLfloat Ship::GetLife() {
  return life_;
}

}  // namespace Play
}  // namespace GameObjects
