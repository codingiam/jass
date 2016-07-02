// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/subsystems/window.h"

#include <boost/format.hpp>

#include <iostream>

#include "jass/utils/debug.h"

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
  this->glew_initialized_ = false;
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
        boost::format("Could not initialise SDL subsystem: %s") %
        SDL_GetError();
    throw std::runtime_error(message.str());
  }

  SDL_ShowCursor(SDL_DISABLE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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

  {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    this->glew_initialized_ = err == GLEW_OK;
    if (!glew_initialized_) {
      boost::format message =
          boost::format("Could not initialise GLEW subsystem: %s") %
          glewGetErrorString(err);
      throw std::runtime_error(message.str());
    }
    glGetError();  // ignore
  }

  // SDL_GL_SetSwapInterval(0);  // vsync

  std::cout << "SDL initialised succesfully. " <<
  "Video information follows: " << std::endl;

  // std::cout << " Screen BPP : " <<
  //   SDL_GetVideoSurface()->format->BitsPerPixel << std::endl;
  std::cout << " Vendor     : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << " Renderer   : " << glGetString(GL_RENDERER) << std::endl;
  std::cout << " Version    : " << glGetString(GL_VERSION) << std::endl;
  // std::cout << " Extensions : " <<
  // glGetString(GL_EXTENSIONS) << std::endl;

  // int value;

  // SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
  // std::cout << " Red component " << value << "b" << std::endl;

  // SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
  // std::cout << " Green component " << value << "b" << std::endl;

  // SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
  // std::cout << " Blue component " << value << "b" << std::endl;

  EnableOpenGLErrorCallback();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glViewport(0, 0, kWidth, kHeight);

  std::cout << "OpenGL initialized." << std::endl;
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
