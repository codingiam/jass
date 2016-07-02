// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/subsystems/gl.h"

#include <GL/glew.h>

#include <boost/format.hpp>

#include <iostream>

#include "jass/utils/debug.h"

namespace Subsystems {

GL::GL() {
  this->subsystem_initialized_ = false;
}

GL::~GL() {
  if (subsystem_initialized_) {
    this->subsystem_initialized_ = false;
  }
}

void GL::Initialize() {
  {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    this->subsystem_initialized_ = err == GLEW_OK;
    if (!subsystem_initialized_) {
      boost::format message =
          boost::format("Could not initialize GLEW: %s") %
          glewGetErrorString(err);
      throw std::runtime_error(message.str());
    }
    glGetError();  // ignore
  }

  EnableOpenGLErrorCallback();

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
