// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SUBSYSTEMS_DEVIL_H_
#define JASS_SUBSYSTEMS_DEVIL_H_

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

#endif  // JASS_SUBSYSTEMS_DEVIL_H_
