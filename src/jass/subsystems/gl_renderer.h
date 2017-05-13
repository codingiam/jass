// Copyright (c) 2016, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SUBSYSTEMS_GL_H_
#define JASS_SUBSYSTEMS_GL_H_

namespace Subsystems {

class GLRenderer {
 public:
  GLRenderer(const GLRenderer &) = delete;
  GLRenderer & operator=(const GLRenderer &) = delete;

  GLRenderer(void);
  ~GLRenderer(void);

  void Initialize(void);

 private:
  bool subsystem_initialized_;
};

}  // namespace Subsystems

#endif  // JASS_SUBSYSTEMS_GL_H_
