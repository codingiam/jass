// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/debug.h"

#include <GL/glew.h>

#include <SDL_opengl.h>

#include <cstdlib>
#include <cstdio>

#ifndef APIENTRY
  #define APIENTRY
#endif

void APIENTRY OpenGLCallbackFunction(GLenum source,
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity,
                                     GLsizei length,
                                     const GLchar *message,
                                     const void *userParam) {
  if (type != GL_DEBUG_TYPE_OTHER) {
    printf("OpenGL error: %s\n", message);
  }
}

void EnableOpenGLErrorCallback() {
  GL_CHECK(glEnable(GL_DEBUG_OUTPUT));

  GL_CHECK(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));

  GL_CHECK(glDebugMessageCallback(OpenGLCallbackFunction, nullptr));

  GLuint unusedIds = 0;

  GL_CHECK(glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
    0, &unusedIds, true));
}

void CheckOpenGLError(const char *stmt, const char *fname, int line) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
    abort();
  }
}
