// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/subsystems/gl_renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <boost/format.hpp>

#include <iostream>

#include "jass/utils/debug.h"

namespace Subsystems {

GLRenderer::GLRenderer() {
  this->subsystem_initialized_ = false;
}

GLRenderer::~GLRenderer() {
  if (subsystem_initialized_) {
    this->subsystem_initialized_ = false;
  }
}

void GLRenderer::Initialize() {
  this->subsystem_initialized_ = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) != 0;

  if (!subsystem_initialized_) {
    throw std::runtime_error("Could not initialize OpenGL Loading Library.");
  }

  InitializeOpenGLErrorCallback();

  std::cout << "Video information follows: " << std::endl;

  std::cout << " Vendor     : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << " Renderer   : " << glGetString(GL_RENDERER) << std::endl;
  std::cout << " Version    : " << glGetString(GL_VERSION) << std::endl;

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glViewport(0, 0, 800, 600);

  std::cout << "OpenGL initialized." << std::endl;
}

}  // namespace Subsystems
