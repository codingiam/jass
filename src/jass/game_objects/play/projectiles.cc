// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/play/projectiles.h"

#include <glm/gtc/constants.hpp>

#include "jass/game_objects/play/ship.h"
#include "jass/drawables/primitives.h"

namespace GameObjects {
namespace Play {

struct Projectile {
  Projectile(GLfloat xpos, GLfloat ypos,
      GLfloat angle, GLuint owner) {
    this->xpos_ = xpos;
    this->ypos_ = ypos;

    this->angle_ = angle;

    this->owner_ = owner;
  }

  void Update(const Uint32 dt) {
    Uint32 diff = dt > 25 ? 25 : dt;

    GLfloat amy = -0.5f * cos(glm::pi<float>() * angle_ / 180);
    GLfloat amx = 0.5f * sin(glm::pi<float>() * angle_ / 180);

    ypos_ += amy * 0.5f * (diff / 25.0f);
    xpos_ += amx * 0.5f * (diff / 25.0f);
  }

  GLuint owner_;
  GLfloat xpos_, ypos_;
  GLfloat angle_;
};

Projectiles::Projectiles() {
}

Projectiles::~Projectiles() {
}

void Projectiles::Update(const Uint32 dt,
      Ship *const red_ship,
      Ship *const blue_ship) {
  for (auto it = projectiles_.begin(); it != projectiles_.end(); ) {
    auto p = &(*it);

    p->Update(dt);

    if ((p->owner_ == 1 && blue_ship->Collide(p->xpos_, p->ypos_)) ||
        (p->owner_ == 2 && red_ship->Collide(p->xpos_, p->ypos_)) ||
        (std::abs(p->xpos_) >= 6.5f || std::abs(p->ypos_) >= 5.5f)) {
      it = projectiles_.erase(it);
    } else {
      ++it;
    }
  }
}

  void Projectiles::Render(Video *const video) {
    const size_t size = projectiles_.size();

    if (size) {
      std::vector<glm::vec2> vertices;
      std::vector<glm::vec3> colors;

      for (auto it = projectiles_.begin(); it != projectiles_.end(); ++it) {
        auto p = *it;
        vertices.push_back(glm::vec2(p.xpos_, p.ypos_));
        colors.push_back(p.owner_ == 1 ?
            glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(0.0f, 0.0f, 1.0f));
      }

      points_->color(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
      points_->translation(glm::vec3(0, 0, -10.f));
      points_->point_size(5.0f);
      points_->vertices(std::move(vertices));
      points_->colors(std::move(colors));
      points_->Render(video);
    }

//    GL_CHECK(glDisable(GL_TEXTURE_2D));
//    GL_CHECK(glDisable(GL_LIGHTING));
//
//    GL_CHECK(glPointSize(5.0f));
//
//    glBegin(GL_POINTS);
//
//    if (owner_ == 1) {
//      glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
//    } else {
//      glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
//    }
//
//    glVertex2f(xpos_, ypos_);
//
//    GL_CHECK(glEnd());
//
//    GL_CHECK(glEnable(GL_LIGHTING));
//    GL_CHECK(glEnable(GL_TEXTURE_2D));
  }

void Projectiles::AddProjectile(GLfloat xpos, GLfloat ypos,
                                            GLfloat angle, GLuint owner) {
  projectiles_.push_back(Projectile(xpos, ypos, angle, owner));
}

void Projectiles::Clear() {
  projectiles_.clear();
}

void Projectiles::Create() {
  this->points_ = std::make_shared<Drawables::Primitives>();
  this->points_->Create();
}

}  // namespace Play
}  // namespace GameObjects
