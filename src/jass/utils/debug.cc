// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "debug.h"

#include <GL/glew.h>

#include <execinfo.h>
#include <malloc.h>

#include <boost/format.hpp>

#include <iostream>

#ifndef APIENTRY
  #define APIENTRY
#endif

void Backtrace() {
  void *array[10];

  int size = backtrace(array, 10);
  char **strings = backtrace_symbols(array, size);

  for (int i = 0; i < size; i++) {
    std::cerr << strings[i] << std::endl;
  }

  free(strings);
}

void APIENTRY OpenGLCallbackFunction(GLenum source,
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity,
                                     GLsizei length,
                                     const GLchar *message,
                                     const void *userParam) {
  if (type != GL_DEBUG_TYPE_OTHER) {
    const GLchar *msg = length > 0 ? message : "";
    std::cerr << boost::format("OpenGL error: source = %08x, type = %08x, "
        "id = %u, severity = %08x, userParam = %08x, message = %s") %
        source % type % id % severity % userParam % msg << std::endl;
  }
}

void EnableOpenGLErrorCallback() {
  GL_CHECK(glEnable(GL_DEBUG_OUTPUT));

  GL_CHECK(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));

  GL_CHECK(glDebugMessageCallback(OpenGLCallbackFunction, nullptr));

  GLuint unusedIds = 0;

  GL_CHECK(glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
    0, &unusedIds, GL_TRUE));
}

void CheckOpenGLError(const char *stmt, const char *fname, int line) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    std::cerr <<
        boost::format("OpenGL error %08x, at %s:%i - for %s") %
        err % fname % line % stmt << std::endl;
    Backtrace();
    throw std::runtime_error("OpenGL call returned an error");
  }
}
