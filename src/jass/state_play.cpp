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
#include "jass/state_introduction.h"
#include "jass/projectile.h"

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

  if (bgSpace) glDeleteTextures( 1, &bgSpace );
  if (bgHealthbar) glDeleteTextures( 1, &bgHealthbar );
  if (bgBoard) glDeleteTextures( 1, &bgBoard );

  for(unsigned int i = 0; i < proiectile.size(); i++) {
    Proiectile* p = proiectile[i];
    delete p;
  }
}

void StatePlay::Create() {
  ship->loadMeshObj("spaceship.obj", "data/obiecte/");

  Video *video = Video::GetVideo();

  SDL_Surface* tmp = video->loadTexture( "data\\texturi\\spacebg.png" );
  video->makeTexture( tmp, bgSpace );
  SDL_FreeSurface( tmp );

  tmp = video->loadTexture( "data\\texturi\\healthbar.png" );
  video->makeTexture( tmp, bgHealthbar );
  SDL_FreeSurface( tmp );

  tmp = video->loadTexture( "data\\texturi\\board.png" );
  video->makeTexture( tmp, bgBoard );
  SDL_FreeSurface( tmp );
}

void StatePlay::Start() {
  nava1 = new Ship( -4.5f, 3.25f, 1, 0.0f );
  nava2 = new Ship( 4.5f, -2.40f, 2, 180.0f );

  Uint32 keys1[] = { SDLK_q, SDLK_s, SDLK_c, SDLK_v, SDLK_LCTRL, 0 };
  nava1->setkeys( keys1 );
  
  Uint32 keys2[] = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_RCTRL, 0 };
  nava2->setkeys( keys2 );
}

void StatePlay::Stop() {
  delete nava1; nava1 = NULL;
  delete nava2; nava2 = NULL;
}

void StatePlay::Execute( Uint32 ticks, Uint8 *keystate ) {
  for(unsigned int i = 0; i < proiectile.size(); i++) {
    Proiectile* p = proiectile[i];
    p->update( ticks );

    Ship* tmp = (p->owner == 1) ? (nava2) : (nava1);
    if (tmp->colide(p->xpos, p->ypos)) p->sterge = true;
  }

  std::vector<Proiectile*>::iterator it;
  if ((it = proiectile.begin()) != proiectile.end())
    do {
      if ((*it)->sterge) {
        delete (*it);
                it = proiectile.erase( it );
      }
      else it++;
    } while (it != proiectile.end());

  nava1->update(ticks, keystate);
  nava2->update(ticks, keystate);

  Video* video = Video::GetVideo();

  glClear( GL_COLOR_BUFFER_BIT ); 
  video->init2DScene( Application::kWidth, Application::kHeight );

  glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
  video->drawTexture( 0, 0, Application::kWidth, Application::kHeight, bgSpace );

  video->init3DScene( Application::kWidth, Application::kHeight );
  
  GLfloat x = .0f, y = .0f, angle = .0f;
  nava1->getPosition(x, y, angle);

  glTranslatef( x, y, -10.0f );
  glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
  glRotatef( angle, 0.0f, 1.0f, 0.0f );
  glScalef( 0.035f, 0.035f, 0.035f );
  glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
  ship->display();
  
  glLoadIdentity();
  nava2->getPosition(x, y, angle);

  glTranslatef( x, y, -10.0f );
  glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
  glRotatef( angle, 0.0f, 1.0f, 0.0f );
  glScalef( 0.035f, 0.035f, 0.035f );
  glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
  ship->display();

  glLoadIdentity();
  glTranslatef( 0.0f, 0.0f, -10.f );
  
  glDisable( GL_TEXTURE_2D ); glDisable( GL_LIGHTING );
    glPointSize( 5.0f );
  glBegin( GL_POINTS );
  for(unsigned int i = 0; i < proiectile.size(); i++) {
    Proiectile* p = proiectile[i];
    p->getPos( x, y );

    if (p->owner == 1) glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
    else glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
    glVertex3f( x, y, 0 );
  }
  glEnd();
    
  glEnable( GL_LIGHTING ); glEnable( GL_TEXTURE_2D );

  video->init2DScene( Application::kWidth, Application::kHeight );

  float life = nava1->getLife();
  glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
  video->drawTexture( 10, 10, 20, 512, bgHealthbar, 1.0f - life );

  life = nava2->getLife();
  video->drawTexture( 770, 10, 20, 512, bgHealthbar, 1.0f - life );

  video->drawTexture( 10, 530, 780, 64, bgBoard );

  SDL_GL_SwapBuffers( );
  
  if (keystate[SDLK_ESCAPE])
      State::set_state(State::Find(kStateIntro).lock().get());

  if ((nava1->getLife() <= 0.0f) || (nava2->getLife() <= 0.0f))
      State::set_state(State::Find(kStateIntro).lock().get());
}

void StatePlay::addProiectile(Proiectile *proiectil) {
  proiectile.push_back(proiectil);
}
