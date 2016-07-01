// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_WINDOW_H_
#define JASS_WINDOW_H_
#pragma once

#include "jass/jass.h"

class Window {
 public:
  enum { kWidth = 800, kHeight = 600, kBpp = 16, kFull = false };

  Window(const Window &) = delete;
  Window & operator=(const Window &) = delete;

  Window(void);
  ~Window(void);

  void Initialize(void);

  void SwapBuffers(void);

 private:
  bool subsystem_initialized_;

  bool glew_initialized_;

  SDL_GLContext gl_context_;
  SDL_Window *sdl_window_;
};

#endif  // JASS_WINDOW_H_