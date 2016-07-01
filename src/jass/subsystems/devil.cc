// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/subsystems/devil.h"

#include <IL/il.h>

namespace Subsystems {

DevIL::DevIL() {
  this->il_initialized_ = false;
}

DevIL::~DevIL() {
  if (il_initialized_) {
    ilShutDown();
    this->il_initialized_ = false;
  }
}

void DevIL::Initialize() {
  ilInit();
  this->il_initialized_ = true;
}

}  // namespace Subsystems
