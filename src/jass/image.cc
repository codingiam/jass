// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/image.h"

#include <string>

Image::Image(void) {
  this->image_ = 0;
}

Image::~Image(void) {
  if (image_) {
    ilDeleteImages(1, &image_);
    this->image_ = 0;
  }
}

bool Image::LoadImage(std::string const &file_name) {
  if (image_) {
    return false;
  }

  this->file_name_ = file_name;

  ilGenImages(1, &this->image_);
  if (ilGetError() != IL_NO_ERROR) {
    return false;
  }

  ilBindImage(image_);
  if (ilGetError() != IL_NO_ERROR) {
    return false;
  }

  bool success = ilLoadImage(file_name.c_str()) == IL_TRUE;
  if (success) {
    success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) == IL_TRUE;
  }

  ilBindImage(0);

  return success;
}

boost::shared_ptr<Image> Image::MakeImage(boost::filesystem::path const &path) {
  boost::shared_ptr<Image> image = boost::shared_ptr<Image>(new Image());

  if (!image->LoadImage(path.string())) {
    boost::format message =
      boost::format("Could not load image: %s") % path.string();
    throw std::runtime_error(message.str());
  }

  return image;
}

bool Image::Callback(
    std::function<void(GLubyte *, GLuint , GLuint)> const &func) {
  if (image_ == 0) {
    return false;
  }

  ilBindImage(image_);
  if (ilGetError() != IL_NO_ERROR) {
    return false;
  }

  func(ilGetData(),
    ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));

  ilBindImage(0);

  return true;
}