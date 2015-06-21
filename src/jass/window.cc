// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/window.h"

#include <string>

Window::Window() {
  this->subsystem_initialized = false;
  this->sdl_window = nullptr;
  this->gl_context = nullptr;
}

Window::~Window() {
  ShutDown();
}

void Window::Initialize() {
  this->subsystem_initialized = SDL_InitSubSystem(SDL_INIT_VIDEO) == 0;
  if (!subsystem_initialized) {
    boost::format message =
      boost::format("Could not initialise SDL subsystem: %s") % SDL_GetError();
    throw std::runtime_error(message.str());
  }

  SDL_ShowCursor(SDL_DISABLE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
    SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);  // SDL_GL_CONTEXT_PROFILE_CORE
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
     SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  Uint32 video_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;  // SDL_HWSURFACE

  if (kFull) {
    video_flags |= SDL_WINDOW_FULLSCREEN;
  }

  this->sdl_window = SDL_CreateWindow("J.A.S.S - Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    kWidth, kHeight,
    video_flags);
  if (!sdl_window) {
    throw std::runtime_error("Could not create window");
  }

  this->gl_context = SDL_GL_CreateContext(sdl_window);
  if (!gl_context) {
    throw std::runtime_error("Could not create OpenGL context");
  }

  SDL_GL_SetSwapInterval(0);  // vsync

  std::cout << "SDL initialised succesfully. " <<
    "Video information follows: " << std::endl;

  // std::cout << " Screen BPP : " <<
  //   SDL_GetVideoSurface()->format->BitsPerPixel << std::endl;
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

  glShadeModel(GL_SMOOTH);  // GL_FLAT

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); \
  // GL_PERSPECTIVE_CORRECTION_HINT ||  GL_LINE_SMOOTH_HINT

  // glPolygonMode(GL_BACK, GL_LINE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glEnable(GL_TEXTURE_2D);

  glViewport(0, 0, kWidth, kHeight);

  std::cout << "OpenGL initialized." << std::endl;
}

void Window::ShutDown() {
  if (gl_context) {
    SDL_GL_DeleteContext(gl_context);
    this->gl_context = nullptr;
  }

  if (sdl_window) {
    SDL_DestroyWindow(sdl_window);
    this->sdl_window = nullptr;
  }

  if (subsystem_initialized) {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    this->subsystem_initialized = false;
  }
}

void Window::SwapBuffers() {
  SDL_GL_SwapWindow(sdl_window);
}
