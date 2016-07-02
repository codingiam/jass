// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_UTILS_DEBUG_H_
#define JASS_UTILS_DEBUG_H_

#if defined(_DEBUG)

#if defined(_WINDOWS)

#include <vld.h>

#endif

void EnableOpenGLErrorCallback(void);

#else

#define GL_CHECK(stmt) stmt

#endif

#endif  // JASS_UTILS_DEBUG_H_
