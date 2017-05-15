// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/subsystems/gl_window.h"

#include <boost/format.hpp>

#include <iostream>
#include <iomanip>

#include "jass/states/state.h"

namespace {

const uint32_t TARGET_FPS = 60;
const double MAX_DT = 1.0;  // second
const double TARGET_DT = MAX_DT / TARGET_FPS;

bool keys_states[GLFW_KEY_LAST + 1] = { false };

void ErrorCallback(int error, const char *description)
{
  fprintf(stderr, "Error: %s\n", description);
  throw std::runtime_error("glfw call returned an error");
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
    int mods)
{
  if (key >= 0 && key <= GLFW_KEY_LAST)
    keys_states[key] = action != GLFW_RELEASE;
}

}

namespace Subsystems {

GLWindow::GLWindow() {
  this->subsystem_initialized_ = false;
  this->window_ = nullptr;
}

GLWindow::~GLWindow() {
  if (window_) {
    glfwDestroyWindow(window_);
    this->window_ = nullptr;
  }

  if (subsystem_initialized_) {
    glfwTerminate();
    this->subsystem_initialized_ = false;
  }
}

void GLWindow::Initialize() {
  glfwSetErrorCallback(ErrorCallback);

  this->subsystem_initialized_ = glfwInit() == GL_TRUE;
  if (!subsystem_initialized_) {
    throw std::runtime_error("Could not initialize GLFW subsystem.");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_ALPHA_BITS, 0);

  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_STENCIL_BITS, 0);

  glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  this->window_ = glfwCreateWindow(kWidth, kHeight, "J.A.S.S - Project",
      NULL, NULL);
  if (!window_) {
    throw std::runtime_error("Could not create window");
  }

  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  glfwSetKeyCallback(window_, KeyCallback);

  glfwMakeContextCurrent(window_);

  glfwSwapInterval(0);

  std::cout << "GLFW initialized succesfully. " << std::endl;
}

void GLWindow::SwapBuffers() {
  glfwSwapBuffers(window_);
}

void GLWindow::Run() {
  double dt = TARGET_DT;
  double last = glfwGetTime();

  while (!glfwWindowShouldClose(window_) && States::State::GetState() != NULL) {
    Tick(dt);

    glfwPollEvents();

    const double now = glfwGetTime();

    dt = now - last;

    if (dt > MAX_DT) {
      dt = TARGET_DT;
    }

    last = now;
  }
}

void GLWindow::Tick(const double dt) {
  States::State::GetState()->Update(dt, keys_states);

  States::State::GetState()->Render();

  SwapBuffers();

  States::State::Swap();
}

}  // namespace Subsystems
