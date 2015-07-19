// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_DEBUG_H_
#define JASS_DEBUG_H_
#pragma once

#if defined(_DEBUG)

#if defined(_WINDOWS)

#include <vld.h>

#endif

namespace {

void CheckOpenGLError(const char *stmt, const char *fname, int line) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
    CheckOpenGLError(stmt, fname, line);
    abort();
  }
}

}  // namespace

#define GL_CHECK(stmt) { \
  stmt; \
  CheckOpenGLError(#stmt, __FILE__, __LINE__); \
}

#else

#define GL_CHECK(stmt) stmt

#endif

#endif  // JASS_DEBUG_H_
