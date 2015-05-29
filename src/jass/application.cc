// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/application.h"

#include "jass/video.h"
#include "jass/state_introduction.h"
#include "jass/state_play.h"

Application::Application() {
  std::cout << "Application being created ..." << std::endl;

  state_intro_ = boost::shared_ptr<StateIntro>(new StateIntro);
  state_play_ = boost::shared_ptr<StatePlay>(new StatePlay); 
}

Application::~Application() {
  Shutdown();

  std::cout << "Application closed." << std::endl;
}

void Application::Initialise() {
  InitialiseSDL();
  //InitialiseFMOD();
  InitialiseStates();
}

void Application::InitialiseStates() {
  State::Register(kStateIntro, state_intro_);
  State::Register(kStatePlay, state_play_);
}

void Application::InitialiseSDL() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    char message[100]; sprintf(message, "Could not initialise SDL: %s", SDL_GetError());
    throw(std::runtime_error(message));
  }

  SDL_ShowCursor(SDL_DISABLE);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 

  Uint32 video_flags = SDL_OPENGLBLIT | SDL_HWSURFACE;

  if (kFull)
    video_flags |= SDL_FULLSCREEN;

  if (SDL_SetVideoMode(kWidth, kHeight, kBpp, video_flags) == NULL)
    throw(std::runtime_error("Could not initialise video mode !"));

  std::cout << "SDL initialised succesfully. Video information follows: " << std::endl;

  std::cout << " Screen BPP : " << SDL_GetVideoSurface()->format->BitsPerPixel << std::endl;
  std::cout << " Vendor     : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << " Renderer   : " << glGetString(GL_RENDERER) << std::endl;
  std::cout << " Version    : " << glGetString(GL_VERSION) << std::endl;
  std::cout << " Extensions : " << glGetString(GL_EXTENSIONS) << std::endl;

  int value;

  SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
  std::cout << " Red component " << value << "b" << std::endl;

  SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
  std::cout << " Green component " << value << "b" << std::endl;

  SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
  std::cout << " Blue component " << value << "b" << std::endl;

  SDL_WM_SetCaption("J.A.S.S - Project", "data/iconita/jass.ico");

  glShadeModel(GL_SMOOTH); // GL_FLAT

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // GL_PERSPECTIVE_CORRECTION_HINT ||  GL_LINE_SMOOTH_HINT

  //glPolygonMode(GL_BACK, GL_LINE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glEnable(GL_TEXTURE_2D);

  glViewport(0, 0, kWidth, kHeight);

  Video * video = Video::GetVideo();
  video->InitFont();

  std::cout << "OpenGL initialised." << std::endl;
}

//void Application::InitialiseFMOD() {
//  if (FSOUND_GetVersion() < FMOD_VERSION) {
//    char mesaj[100]; sprintf_s( mesaj, 100, "Veriune FMOD inavlida, ar trebui sa fie : %.02f", FMOD_VERSION );
//    throw( std::runtime_error( mesaj ) );
//  }
//
//  bool retval = (FSOUND_SetOutput( -1 ) == TRUE);
//  retval &= (FSOUND_SetDriver( 0 ) == TRUE);
//  retval &= (FSOUND_Init(44100, 32, FSOUND_INIT_USEDEFAULTMIDISYNTH) == TRUE);
//
//  if (!retval) {
//    throw( std::runtime_error( "Nu am putut initializa FMOD !" ) );
//  }
//
//  intromusic = FMUSIC_LoadSong( "data\\muzica\\intro.s3m" );
//  if (!intromusic) {
//    throw( std::runtime_error( "Nu am putut incarca data\\muzica\\intro.s3m" ) );
//  }
//  std::cout << "data\\muzica\\intro.s3m a fost incarcat" << std::endl;
//
//  FMUSIC_PlaySong( intromusic );
//
//  std::cout << "FMOD a fost initializat." << std::endl;
//}

void Application::Run() {
  Uint32 milliseconds = 0;
  Uint8 * keys_state = NULL;
  State * state = NULL;

  SDL_Event sdl_event;

  State::set_state(state_intro_.get());
  State::Update();

  while ((state = State::state()) != NULL) {
    milliseconds = SDL_GetTicks();

    SDL_PumpEvents();

    keys_state = SDL_GetKeyState(NULL);

    state->Execute(milliseconds, keys_state);

    if (keys_state[SDLK_F10])
      State::set_state(NULL);

    while (SDL_PollEvent(&sdl_event)) {
      if (sdl_event.type == SDL_QUIT)
        State::set_state(NULL);
    }

    State::Update();
  }
}

void Application::Shutdown() {
  State::Unregister(kStatePlay);
  State::Unregister(kStateIntro);

  //if (intro_music_) {
  //  FMUSIC_StopAllSongs();
  //  FMUSIC_FreeSong(intro_music_);
  //}
  //FSOUND_Close();

  SDL_Quit();
}