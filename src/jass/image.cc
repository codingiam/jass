// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/image.h"

#include <string>

Image::Image(void) {
  this->texid_ = 0;
}

Image::~Image(void) {
  if (texid_) {
    ilDeleteImages(1, &texid_);
    this->texid_ = 0;
  }
}

bool Image::loadImage(std::string const &file_name) {
  if (texid_) {
    return false;
  }

  ilGenImages(1, &this->texid_);

  ilBindImage(texid_);

  bool loaded = ilLoadImage(file_name.c_str()) == IL_TRUE;
  if (loaded) {
    loaded = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) == IL_TRUE;
  }

  ilBindImage(0);

  return loaded;
}
