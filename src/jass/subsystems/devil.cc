// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/subsystems/devil.h"

#include <IL/il.h>

namespace Subsystems {

DevIL::DevIL() {
  this->subsystem_initialized_ = false;
}

DevIL::~DevIL() {
  if (subsystem_initialized_) {
    ilShutDown();
    this->subsystem_initialized_ = false;
  }
}

void DevIL::Initialize() {
  ilInit();
  this->subsystem_initialized_ = true;
}

}  // namespace Subsystems
