// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/jass.h"

class Image : boost::noncopyable
{
 public:
  Image(void);
  ~Image(void);

  bool loadImage(std::string const &file_name);
  
  template<typename Func>
  void withData (Func func) {
    ilBindImage(texid_);

    func((GLuint *) ilGetData(), (GLuint)ilGetInteger( IL_IMAGE_WIDTH ), (GLuint)ilGetInteger( IL_IMAGE_HEIGHT ));

    ilBindImage(0);
  };

 private:
  ILuint texid_;
};
