// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SUBSYSTEMS_WINDOW_H_
#define JASS_SUBSYSTEMS_WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Subsystems {

class Window {
 public:
  enum { kWidth = 800, kHeight = 600, /*kBpp = 24, kFull = false */};

  Window(const Window &) = delete;
  Window & operator=(const Window &) = delete;

  Window(void);
  ~Window(void);

  void Initialize(void);

  void Run(void);

  void SwapBuffers(void);

 private:
  void Tick(const double dt);

  bool subsystem_initialized_;

  GLFWwindow *window_;
};

}  // namespace Subsystems

#endif  // JASS_SUBSYSTEMS_WINDOW_H_
