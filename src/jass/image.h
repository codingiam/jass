// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_IMAGE_H_
#define JASS_SRC_JASS_IMAGE_H_
#pragma once

#include <string>

#include "jass/jass.h"

class Image : boost::noncopyable {
 public:
  Image(void);
  ~Image(void);

  bool loadImage(std::string const &file_name);

  template<typename Func>
  void withData(Func func) {
    ilBindImage(texid_);

    func(ilGetData(),
      ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));

    ilBindImage(0);
  }

 private:
  ILuint texid_;
};

#endif  // JASS_SRC_JASS_IMAGE_H_
