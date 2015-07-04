// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_VIDEO_H_
#define JASS_VIDEO_H_
#pragma once

#include <glm/vec3.hpp>

#include "jass/jass.h"

class Image;
class Texture;

class Video : private boost::noncopyable {
 public:
  Video(void);
  ~Video(void);

  void Initialize(void);

  void Init2DScene(int width, int height);
  void Init3DScene(int width, int height);

  void LoadFont(void);

  void Print(GLint x, GLint y, const char* text, int set = 1);

  void DrawTexture(int x, int y, int w, int h,
    std::shared_ptr<Texture> const &texture, GLfloat yamount = 0.0f);

  glm::vec3 GetNormal(const glm::vec3 v0, const glm::vec3 v1,
    const glm::vec3 v2);

 private:
  bool il_initialized_;

  std::shared_ptr<Texture> font_texture_;
  GLuint base_;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  enum { rmask = 0xff000000, gmask = 0x00ff0000,
    bmask = 0x0000ff00, amask = 0x000000ff };
#else
  enum { rmask = 0x000000ff, gmask = 0x0000ff00,
    bmask = 0x00ff0000, amask = 0xff000000 };
#endif
};

#endif  // JASS_VIDEO_H_
