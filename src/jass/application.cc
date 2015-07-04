// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/application.h"

#include "jass/video.h"
#include "jass/state.h"
#include "jass/window.h"
#include "jass/states_manager.h"

namespace {
  const Uint32 TARGET_FPS = 60;
  const Uint32 MAX_DT = 1000;  // ms

  const Uint32 TARGET_DT = MAX_DT / TARGET_FPS;
}

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
  states_manager_.reset();

  window_.reset();

  if (sdl_initialized_) {
    this->sdl_initialized_ = false;
    SDL_Quit();
  }
}

void Application::InitializeWindow() {
  this->window_ = std::shared_ptr<Window>(new Window());
  window_->Initialize();
}

void Application::InitializeVideo() {
  this->video_ = std::shared_ptr<Video>(new Video());
  video_->Initialize();
}

void Application::InitialiseStates() {
  this->states_manager_ = std::shared_ptr<StatesManager>(new StatesManager());
  states_manager_->Initialize(this->video_.get());
}

void Application::Run() {
  Uint32 dt = TARGET_DT;
  Uint32 begin_ms = SDL_GetTicks();

  while (State::GetState() != NULL) {
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

    State::GetState()->Update(dt, keys_state);

    State::GetState()->Render(video_.get());

    window_->SwapBuffers();

    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event)) {
      if (sdl_event.type == SDL_QUIT) {
        State::SetState(NULL);
      }
    }

    State::Swap();
}
