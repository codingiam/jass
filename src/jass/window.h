// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_WINDOW_H_
#define JASS_SRC_JASS_WINDOW_H_
#pragma once

#include "jass/jass.h"

class Window : boost::noncopyable {
 public:
  enum { kWidth = 800, kHeight = 600, kBpp = 16, kFull = 0 };

  Window(void);
  ~Window(void);

  void Initialize(void);
  void ShutDown(void);

  void SwapBuffers(void);

 private:
  bool subsystem_initialized;
  
  SDL_GLContext gl_context;
  SDL_Window *sdl_window;
};

#endif  // JASS_SRC_JASS_WINDOW_H_
