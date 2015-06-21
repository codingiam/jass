// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/state_introduction.h"

#include "jass/video.h"
#include "jass/application.h"
#include "jass/states_manager.h"
#include "jass/window.h"

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
  bgSpace = 0;
  bgIntro = 0;
  bgAction = 0;

  ticksTitle = 0;
  ticksAction = 0;
  ticksIntroText = 0;
  
  speedTitle = 1 * 1000;
  speedAction = 2 * 1000;
  speedIntroText = 10 * 1000;
    
  sizeIntroText = 0;

    for (int i = 0; i < 7; i++) {
      sizeIntroText += strlen(introText[i]); //introText[i].length();
    }
}

StateIntro::~StateIntro() {
  if (bgSpace) glDeleteTextures( 1, &bgSpace );
  if (bgIntro) glDeleteTextures( 1, &bgSpace );
  if (bgAction) glDeleteTextures( 1, &bgAction );
}

void StateIntro::Create() {
  Video* video = Video::GetVideo();
  //std::cout << video->fontTexture << std::endl;

  boost::shared_ptr<Image> tmp = video->loadImage( "data\\texturi\\introbg.png" );
  video->makeTexture( tmp, bgSpace );

  tmp = video->loadImage( "data\\texturi\\title.png" );
  video->makeTexture( tmp, bgIntro );

  tmp = video->loadImage( "data\\texturi\\action.png" );
  video->makeTexture( tmp, bgAction );

  if (!(bgSpace) || !(bgIntro) || !(bgAction)) {
    throw( std::runtime_error( "Nu am putut crea texturile pentru 'stateintro'." ) );
  }
}

void StateIntro::Start() {
  ticksTitle = 0;
  ticksAction = 0;
  ticksIntroText = 0;
}

void StateIntro::Stop() {
}

void StateIntro::Execute(const Uint32 dt, const Uint8 *keystate) {
  ticksTitle += dt;
  ticksAction += dt;
  ticksIntroText += dt;
  
  alphaTitle = (float) ticksTitle / (float) speedTitle;
  blueAction = (float) ticksAction / (float) speedAction;
  positionText = (float) ticksIntroText / (float) speedIntroText;

  if (alphaTitle >= 1.0f) alphaTitle = 1.0f;
  if (blueAction >= 1.0f) ticksAction -= speedAction;
  if (positionText >= 1.0f) positionText = 1.0f;

  showTo = (Uint32) (sizeIntroText * positionText);

  if (keystate[SDL_SCANCODE_SPACE])
      State::set_state(State::Find(kStatePlay).lock().get());

  if (keystate[SDL_SCANCODE_F10])
      State::set_state(NULL);
}

void StateIntro::Render(Video *const video) {
  glClear( GL_COLOR_BUFFER_BIT ); 
  video->init2DScene( Window::kWidth, Window::kHeight );
  
  glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
  video->drawTexture( 0, 0, Window::kWidth, Window::kHeight, bgSpace );

  glColor4f( 1.0f, 1.0f, 1.0f, alphaTitle );
  video->drawTexture( 272, 8, 256, 64, bgIntro );

  glColor4f( 1.0f, 1.0f - blueAction, blueAction, 1.0f );
  video->drawTexture( 262, 440, 276, 64, bgAction );

  glColor3f( 1.0f, 1.0f, 1.0f );

  Uint32 marime = 0;
  char buffer[100 + 1];

  for (int i = 0; showTo > 0; i++) {
    marime = strlen(introText[i]); //introText[i].length();
    if (marime > showTo) marime = showTo;
        if (marime > 100) marime = 100;
        //size_t copied = introText[i].copy(buffer, marime);
        strncpy(buffer, introText[i], marime);
        buffer[marime] = '\0';
    showTo -= marime;
    video->print( 90, 105 + 20 * i, buffer);
  }
}
