// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/resources/image.h"

#include <boost/format.hpp>

namespace Resources {

Image::Image(void) {
  this->image_ = 0;
  this->width_ = 0;
  this->height_ = 0;
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

  if (success) {
    this->width_ = static_cast<ILuint>(ilGetInteger(IL_IMAGE_WIDTH));
    if (ilGetError() != IL_NO_ERROR) {
      this->width_ = 0;
      success = false;
    }

    this->height_ = static_cast<ILuint>(ilGetInteger(IL_IMAGE_HEIGHT));
    if (ilGetError() != IL_NO_ERROR) {
      this->height_ = 0;
      success = false;
    }
  }

  ilBindImage(0);

  return success;
}

std::shared_ptr<Image> Image::MakeImage(boost::filesystem::path const &path) {
  std::shared_ptr<Image> image = std::make_shared<Image>();

  if (!image->LoadImage(path.string())) {
    boost::format message =
      boost::format("Could not load image: %s") % path.string();
    throw std::runtime_error(message.str());
  }

  return image;
}

bool Image::Bind(
    std::function<void(GLubyte *, GLuint , GLuint)> const &func) {
  if (image_ == 0) {
    return false;
  }

  ilBindImage(image_);
  if (ilGetError() != IL_NO_ERROR) {
    return false;
  }

  func(ilGetData(), width_, height_);

  ilBindImage(0);

  return true;
}

}  // namespace Resources
