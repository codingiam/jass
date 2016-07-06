// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/subsystems/window.h"

#include <boost/format.hpp>

#include <iostream>

#include "jass/states/state.h"

namespace {
const uint32_t TARGET_FPS = 60;
const uint32_t MAX_DT = 1000;  // ms

const uint32_t TARGET_DT = MAX_DT / TARGET_FPS;
}

namespace Subsystems {

Window::Window() {
  this->subsystem_initialized_ = false;
  this->sdl_window_ = nullptr;
  this->gl_context_ = nullptr;
}

Window::~Window() {
  if (gl_context_) {
    SDL_GL_DeleteContext(gl_context_);
    this->gl_context_ = nullptr;
  }

  if (sdl_window_) {
    SDL_DestroyWindow(sdl_window_);
    this->sdl_window_ = nullptr;
  }

  if (subsystem_initialized_) {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    this->subsystem_initialized_ = false;
  }
}

void Window::Initialize() {
  this->subsystem_initialized_ = SDL_InitSubSystem(SDL_INIT_VIDEO) == 0;
  if (!subsystem_initialized_) {
    boost::format message =
        boost::format("Could not initialize SDL subsystem: %s") %
        SDL_GetError();
    throw std::runtime_error(message.str());
  }

  SDL_ShowCursor(SDL_DISABLE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
      SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  uint32_t video_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;  // SDL_HWSURFACE

//  if (kFull == (true)) {
//    video_flags |= SDL_WINDOW_FULLSCREEN;
//  }

  this->sdl_window_ = SDL_CreateWindow("J.A.S.S - Project",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      kWidth, kHeight,
      video_flags);
  if (!sdl_window_) {
    throw std::runtime_error("Could not create window");
  }

  this->gl_context_ = SDL_GL_CreateContext(sdl_window_);
  if (!gl_context_) {
    boost::format message =
        boost::format("Could not create OpenGL context: %s") % SDL_GetError();
    throw std::runtime_error(message.str());
  }

  if (SDL_GL_SetSwapInterval(0) == -1) {
    std::cerr << "Could not configure swap interval. " << std::endl;
  }

  std::cout << "SDL initialized succesfully. " << std::endl;
}

void Window::SwapBuffers() {
  SDL_GL_SwapWindow(sdl_window_);
}

void Window::Run() {
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

void Window::Tick(const uint32_t dt) {
  const uint8_t *keys_state = SDL_GetKeyboardState(NULL);

  States::State::GetState()->Update(dt, keys_state);

  States::State::GetState()->Render();

  SwapBuffers();

  SDL_Event sdl_event;

  while (SDL_PollEvent(&sdl_event)) {
    if (sdl_event.type == SDL_QUIT) {
      States::State::SetState(NULL);
    }
  }

  States::State::Swap();
}

}  // namespace Subsystems
