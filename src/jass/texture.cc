// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/texture.h"

#include "jass/image.h"

Texture::Texture() {
  this->texture_ = 0;
}

Texture::~Texture() {
  if (texture_) {
    glDeleteTextures(1, &texture_);
    this->texture_ = 0;
  }
}

bool Texture::LoadTexture(boost::shared_ptr<Image> const &image) {
  if (texture_) {
    return false;
  }

  glGenTextures(1, &texture_);
  if (glGetError() != GL_NO_ERROR) {
    return false;
  }

  const GLuint *texture = &texture_;

  std::function<void(GLubyte *, GLuint , GLuint)> func =
      [texture] (GLubyte *pixels, GLuint width, GLuint height) {
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
      0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
  };

  return image->Callback(func);
}

boost::shared_ptr<Texture> Texture::MakeTexture(
    boost::shared_ptr<Image> const &image) {
  boost::shared_ptr<Texture> texture =
    boost::shared_ptr<Texture>(new Texture());

  if (!texture->LoadTexture(image)) {
    boost::format message =
      boost::format("Could not create texture: %s") % image->file_name();
    throw std::runtime_error(message.str());
  }

  return texture;
}

bool Texture::Callback(std::function<void(void)> const &func) {
  if (texture_ == 0) {
    return false;
  }

  glBindTexture(GL_TEXTURE_2D, texture_);
  if (glGetError() != GL_NO_ERROR) {
    return false;
  }

  func();

  glBindTexture(GL_TEXTURE_2D, 0);

  return true;
}

bool Texture::Bind(void) {
  if (texture_ == 0) {
    return false;
  }

  glBindTexture(GL_TEXTURE_2D, texture_);
  if (glGetError != GL_NO_ERROR) {
    return false;
  }

  return true;
}