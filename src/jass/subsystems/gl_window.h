// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SUBSYSTEMS_WINDOW_H_
#define JASS_SUBSYSTEMS_WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Subsystems {

class GLWindow {
 public:
  enum { kWidth = 800, kHeight = 600, /*kBpp = 24, kFull = false */};

  GLWindow(const GLWindow &) = delete;
  GLWindow & operator=(const GLWindow &) = delete;

  GLWindow(void);
  ~GLWindow(void);

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
