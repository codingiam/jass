// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/application.h"

#include "jass/video.h"
#include "jass/state.h"
#include "jass/window.h"
#include "jass/states_manager.h"

const Uint32 TARGET_FPS = 60;
const Uint32 MAX_DT = 1000;  // ms

const Uint32 TARGET_DT = MAX_DT / TARGET_FPS;

Application::Application() {
  std::cout << "Application being constructed ..." << std::endl;
  this->sdl_initialized_ = false;
}

Application::~Application() {
  ShutDown();
  std::cout << "Application destroyed." << std::endl;
}

void Application::Initialize() {
  this->sdl_initialized_ = SDL_Init(SDL_INIT_TIMER) == 0;
  if (!sdl_initialized_) {
    boost::format message =
      boost::format("Could not initialise SDL: %s") % SDL_GetError();
    throw std::runtime_error(message.str());
  }

  InitializeWindow();
  InitializeVideo();
  InitialiseStates();
}

void Application::ShutDown() {
  this->states_manager_ = boost::shared_ptr<StatesManager>();

  this->window_ = boost::shared_ptr<Window>();

  if (sdl_initialized_) {
    this->sdl_initialized_ = false;
    SDL_Quit();
  }
}

void Application::InitializeWindow() {
  this->window_ = boost::shared_ptr<Window>(new Window);
  window_->Initialize();
}

void Application::InitializeVideo() {
  Video *video = Video::GetVideo();
  video->InitFont();
}

void Application::InitialiseStates() {
  this->states_manager_ = boost::shared_ptr<StatesManager>(new StatesManager);
  states_manager_->Initialize();
}

void Application::Run() {
  Uint32 dt = TARGET_DT;
  Uint32 begin_ms = SDL_GetTicks();

  while (State::state() != NULL) {
    Tick(dt);

    const Uint32 end_ms = SDL_GetTicks();

    dt = end_ms - begin_ms;

    if (dt > MAX_DT) {
      dt = TARGET_DT;
    }

    begin_ms = end_ms;
  }
}

void Application::Tick(const Uint32 dt) {
    const Uint8 *keys_state = SDL_GetKeyboardState(NULL);

    State::state()->Execute(dt, keys_state);

    State::state()->Render(Video::GetVideo());

    window_->SwapBuffers();

    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event)) {
      if (sdl_event.type == SDL_QUIT) {
        State::set_state(NULL);
      }
    }

    State::Update();
}
