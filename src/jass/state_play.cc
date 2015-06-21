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

StatePlay::StatePlay() {
  bgSpace = 0;
  bgHealthbar = 0;
  bgBoard = 0;

  ship = new Mesh();

  nava1 = NULL;
  nava2 = NULL;
}

StatePlay::~StatePlay() {
  delete ship;

  delete nava1;
  delete nava2;

  if (bgSpace) glDeleteTextures(1, &bgSpace);
  if (bgHealthbar) glDeleteTextures(1, &bgHealthbar);
  if (bgBoard) glDeleteTextures(1, &bgBoard);

  for (unsigned int i = 0; i < proiectile.size(); i++) {
    Proiectile* p = proiectile[i];
    delete p;
  }
}

void StatePlay::Create() {
  ship->loadMeshObj("spaceship.obj", "data/obiecte/");

  Video *video = Video::GetVideo();

  boost::shared_ptr<Image> tmp = video->loadImage("data\\texturi\\spacebg.png");
  video->makeTexture(tmp, &bgSpace);

  tmp = video->loadImage("data\\texturi\\healthbar.png");
  video->makeTexture(tmp, &bgHealthbar);

  tmp = video->loadImage("data\\texturi\\board.png");
  video->makeTexture(tmp, &bgBoard);
}

void StatePlay::Start() {
  nava1 = new Ship(-4.5f, 3.25f, 1, 0.0f);
  nava2 = new Ship(4.5f, -2.40f, 2, 180.0f);

  Uint32 keys1[] = { SDL_SCANCODE_Q, SDL_SCANCODE_S, SDL_SCANCODE_C,
    SDL_SCANCODE_V, SDL_SCANCODE_LCTRL, 0 };
  nava1->setkeys(keys1);

  Uint32 keys2[] = { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL, 0 };
  nava2->setkeys(keys2);
}

void StatePlay::Stop() {
  delete nava1; nava1 = NULL;
  delete nava2; nava2 = NULL;
}

void StatePlay::Execute(const Uint32 dt, const Uint8 *keystate) {
  for (unsigned int i = 0; i < proiectile.size(); i++) {
    Proiectile* p = proiectile[i];
    p->update(dt);

    Ship* tmp = (p->owner == 1) ? (nava2) : (nava1);
    if (tmp->colide(p->xpos, p->ypos)) p->sterge = true;
  }

  std::vector<Proiectile*>::iterator it;
  if ((it = proiectile.begin()) != proiectile.end()) {
    do {
      if ((*it)->sterge) {
        delete (*it);
                it = proiectile.erase(it);
      } else {
        it++;
      }
    } while (it != proiectile.end());
  }

  nava1->update(dt, keystate);
  nava2->update(dt, keystate);

  if (keystate[SDL_SCANCODE_ESCAPE])
      State::set_state(State::Find(kStateIntro).lock().get());

  if ((nava1->getLife() <= 0.0f) || (nava2->getLife() <= 0.0f))
      State::set_state(State::Find(kStateIntro).lock().get());
}

void StatePlay::addProiectile(Proiectile *proiectil) {
  proiectile.push_back(proiectil);
}

void StatePlay::Render(Video *const video) {
  glClear(GL_COLOR_BUFFER_BIT);
  video->init2DScene(Window::kWidth, Window::kHeight);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  video->drawTexture(0, 0, Window::kWidth, Window::kHeight, bgSpace);

  video->init3DScene(Window::kWidth, Window::kHeight);

  glPushMatrix();

  GLfloat x = .0f, y = .0f, angle = .0f;
  nava1->getPosition(&x, &y, &angle);

  glTranslatef(x, y, -10.0f);
  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glScalef(0.035f, 0.035f, 0.035f);
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  ship->display();

  glPopMatrix();
  glPushMatrix();

  nava2->getPosition(&x, &y, &angle);

  glTranslatef(x, y, -10.0f);
  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glScalef(0.035f, 0.035f, 0.035f);
  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
  ship->display();

  glPopMatrix();

  glTranslatef(0.0f, 0.0f, -10.f);

  glDisable(GL_TEXTURE_2D); glDisable(GL_LIGHTING);
    glPointSize(5.0f);
  glBegin(GL_POINTS);
  for (unsigned int i = 0; i < proiectile.size(); i++) {
    Proiectile* p = proiectile[i];
    p->getPos(&x, &y);

    if (p->owner == 1) {
      glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    } else {
      glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    }
    glVertex3f(x, y, 0);
  }
  glEnd();

  glEnable(GL_LIGHTING); glEnable(GL_TEXTURE_2D);

  video->init2DScene(Window::kWidth, Window::kHeight);

  float life = nava1->getLife();
  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
  video->drawTexture(10, 10, 20, 512, bgHealthbar, 1.0f - life);

  life = nava2->getLife();
  video->drawTexture(770, 10, 20, 512, bgHealthbar, 1.0f - life);

  video->drawTexture(10, 530, 780, 64, bgBoard);
}
