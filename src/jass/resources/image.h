// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_RESOURCES_IMAGE_H_
#define JASS_RESOURCES_IMAGE_H_

#include <glad/glad.h>

#include <il.h>

#include <boost/filesystem.hpp>

#include <string>

namespace Resources {

class Image {
 public:
  Image(const Image &) = delete;
  Image & operator=(const Image &) = delete;

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
  ILuint width_;
  ILuint height_;
};

}  // namespace Resources

#endif  // JASS_RESOURCES_IMAGE_H_
