// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_JASS_H_
#define JASS_JASS_H_
#pragma once

#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <IL/il.h>

#include <boost/noncopyable.hpp>
#include <boost/format.hpp>

#include <iostream>

#include <stdexcept>

#include "jass/debug.h"

#ifdef _WINDOWS
  #define snprintf _snprintf
#endif

#endif  // JASS_JASS_H_
