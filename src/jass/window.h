// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_WINDOW_H_
#define JASS_WINDOW_H_
#pragma once

#include "jass/jass.h"

class Window : private boost::noncopyable {
 public:
  enum { kWidth = 800, kHeight = 600, kBpp = 16, kFull = false };

  Window(void);
  ~Window(void);

  void Initialize(void);

  void SwapBuffers(void);

 private:
  bool subsystem_initialized_;

  bool glew__initialized_;

  SDL_GLContext gl_context_;
  SDL_Window *sdl_window_;
};

#endif  // JASS_WINDOW_H_
