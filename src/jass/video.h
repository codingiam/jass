// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_VIDEO_H_
#define JASS_VIDEO_H_
#pragma once

#include <glm/vec3.hpp>
#include <boost/filesystem.hpp>

#include "jass/jass.h"

class Image;

class Video : boost::noncopyable {
 public:
  static Video* GetVideo() {
    static Video video;
    return &video;
  }

  ~Video();

  void init2DScene(int width, int height);
  void init3DScene(int width, int height);
  void InitFont();
  void print(GLint x, GLint y, const char* text, int set = 1);
  // SDL_Surface* loadImage(char* name);
  boost::shared_ptr<Image> loadImage(boost::filesystem::path const &path);
  // void makeTexture(SDL_Surface* surface, GLuint& texture);
  void makeTexture(boost::shared_ptr<Image> const &image, GLuint *texture);
  void drawTexture(int x, int y, int w, int h,
    GLuint texture, GLfloat yamount = 0.0f);
  glm::vec3 getNormal(const glm::vec3 v0, const glm::vec3 v1,
    const glm::vec3 v2);

  void plusZpos();
  void minusZpos();

  GLuint fontTexture;
  GLuint base;

 private:
  SDL_Surface *IMG_Load(const char *file);
  GLfloat zpos;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  enum { rmask = 0xff000000, gmask = 0x00ff0000,
    bmask = 0x0000ff00, amask = 0x000000ff };
#else
  enum { rmask = 0x000000ff, gmask = 0x0000ff00,
    bmask = 0x00ff0000, amask = 0xff000000 };
#endif
  Video();
};

#endif  // JASS_VIDEO_H_
