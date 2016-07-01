// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_VIDEO_H_
#define JASS_VIDEO_H_
#pragma once

namespace Subsystems {

class DevIL {
 public:
  DevIL(const DevIL &) = delete;
  DevIL & operator=(const DevIL &) = delete;

  DevIL(void);
  ~DevIL(void);

  void Initialize(void);

 private:
  bool il_initialized_;
};

}  // namespace Subsystems

#endif  // JASS_VIDEO_H_
