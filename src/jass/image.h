// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_IMAGE_H_
#define JASS_IMAGE_H_
#pragma once

#include <boost/filesystem.hpp>

#include <string>

#include "jass/jass.h"

class Image : private boost::noncopyable {
 public:
  Image(void);
  ~Image(void);

  bool LoadImage(std::string const &file_name);

  static std::shared_ptr<Image>
    MakeImage(boost::filesystem::path const &path);

  bool Bind(std::function<void(GLubyte *, GLuint , GLuint)> const &func);

  std::string file_name() const { return file_name_; }

  ILint width(void) { return width_; }
  ILint height(void) { return height_; }

 private:
  ILuint image_;
  std::string file_name_;
  ILint width_;
  ILint height_;
};

#endif  // JASS_IMAGE_H_
