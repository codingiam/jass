// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/application.h"

#include <boost/format.hpp>

#include <iostream>

#include "jass/subsystems/devil.h"
#include "jass/states/state.h"
#include "jass/subsystems/window.h"
#include "jass/states/states_manager.h"

namespace {
  const uint32_t TARGET_FPS = 60;
  const uint32_t MAX_DT = 1000;  // ms

  const uint32_t TARGET_DT = MAX_DT / TARGET_FPS;
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

  video_.reset();

  window_.reset();

  if (sdl_initialized_) {
    this->sdl_initialized_ = false;
    SDL_Quit();
  }
}

void Application::InitializeWindow() {
  this->window_ = std::make_shared<Subsystems::Window>();
  window_->Initialize();
}

void Application::InitializeVideo() {
  this->video_ = std::make_shared<Subsystems::DevIL>();
  video_->Initialize();
}

void Application::InitialiseStates() {
  this->states_manager_ = std::make_shared<States::StatesManager>();
  states_manager_->Initialize();
}

void Application::Run() {
  uint32_t dt = TARGET_DT;
  uint32_t begin_ms = SDL_GetTicks();

  while (States::State::GetState() != NULL) {
    Tick(dt);

    const uint32_t end_ms = SDL_GetTicks();

    dt = end_ms - begin_ms;

    if (dt > MAX_DT) {
      dt = TARGET_DT;
    }

    begin_ms = end_ms;
  }
}

void Application::Tick(const uint32_t dt) {
    const uint8_t *keys_state = SDL_GetKeyboardState(NULL);

    States::State::GetState()->Update(dt, keys_state);

    States::State::GetState()->Render();

    window_->SwapBuffers();

    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event)) {
      if (sdl_event.type == SDL_QUIT) {
        States::State::SetState(NULL);
      }
    }

    States::State::Swap();
}
