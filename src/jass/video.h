// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_VIDEO_H_
#define JASS_SRC_JASS_VIDEO_H_
#pragma once

#include "jass/jass.h"

typedef GLint vertex2i[2];
typedef GLfloat vertex3f[3];

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
  void print(GLint x, GLint y, const char* string, int set = 1);
  SDL_Surface* loadTexture(char* name);
  void makeTexture(SDL_Surface* surface, GLuint& texture);
  void drawTexture(int x, int y, int w, int h, GLuint texture, GLfloat yamount = 0.0f);
  void getNormal(vertex3f v0, vertex3f v1, vertex3f v2, vertex3f& normal);

  GLuint fontTexture;
  GLuint base;

private:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  enum { rmask = 0xff000000, gmask = 0x00ff0000, bmask = 0x0000ff00, amask = 0x000000ff };
#else
  enum { rmask = 0x000000ff, gmask = 0x0000ff00, bmask = 0x00ff0000, amask = 0xff000000 };
#endif    
  Video();
};

#endif  // JASS_SRC_JASS_VIDEO_H_
