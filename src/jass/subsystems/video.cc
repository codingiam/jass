// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "video.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sstream>
#include <cmath>
#include <string>

#include "jass/application.h"

#include "jass/resources/image.h"
#include "jass/gl/texture.h"

namespace {

// void perspectiveGL(GLdouble fovY, GLdouble aspect,
//                           GLdouble zNear, GLdouble zFar) {
//   glm::mat4 persp = glm::perspective(fovY, aspect, zNear, zFar);
//   GL_CHECK(glLoadMatrixf(glm::value_ptr(persp)));
// }

// void ortho2D(GLdouble left, GLdouble right,
//                     GLdouble bottom, GLdouble top) {
//   glm::mat4 ortho = glm::ortho(left, right, bottom, top);
//   GL_CHECK(glLoadMatrixf(glm::value_ptr(ortho)));
// }

}  // namespace

Video::Video() {
  this->il_initialized_ = false;
  this->font_texture_ = 0;
//  this->base_ = 0;
}

Video::~Video() {
  if (il_initialized_) {
    ilShutDown();
    this->il_initialized_ = false;
  }

//  if (base_) {
//    GL_CHECK(glDeleteLists(base_, 256));
//    this->base_ = 0;
//  }

  font_texture_.reset();
}

void Video::Initialize() {
  ilInit();
  this->il_initialized_ = true;

  LoadFont();
}

void Video::LoadFont() {
  if (font_texture_)
    return;

  std::shared_ptr<Image> image = Image::MakeImage("resources/fonts/font.png");
  this->font_texture_ = Texture::MakeTexture(image);
/*
  GL_CHECK(this->base_ = glGenLists(256));

  const GLuint base = base_;

  std::function<void(void)> func = [base] () {
    float cx = 0, cy = 0;

    for (int loop = 0; loop < 256; loop++) {

      GL_CHECK(glNewList(base + loop, GL_COMPILE));
      
      glBegin(GL_TRIANGLE_STRIP);

      glTexCoord2f(cx / 256, cy / 256);
      glVertex2i(0, 0);

      glTexCoord2f(cx / 256, (cy + 16) / 256);
      glVertex2i(0, 16);

      glTexCoord2f((cx + 16) / 256, cy / 256);
      glVertex2i(16, 0);

      glTexCoord2f((cx + 16) / 256, (cy + 16) / 256);
      glVertex2i(16, 16);
      
      GL_CHECK(glEnd());

      GL_CHECK(glTranslated(10, 0, 0));
      GL_CHECK(glEndList());

      cx += 16;
      if (fabs(cx - 256) <= .1f) {
        cx = 0;
        cy += 16;
      }
    }
};

  font_texture_->Bind(func);
 */
}

void Video::Print(GLint x, GLint y, const char *text, int set) {
  std::function<void(void)> func = [x, y, text] () {
    const char *p;
    float x2 = x, y2 = y, w = 16, h = 16;

    for(p = text; *p; p++) {
      GLfloat box[4][4] = {
        {x2,     -y2    , 0, 0},
        {x2 + w, -y2    , 1, 0},
        {x2,     -y2 - h, 0, 1},
        {x2 + w, -y2 - h, 1, 1},
      };

      GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW));
      GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));

      x2 += 16;
    }

    /*
    GL_CHECK(glLoadIdentity());

    GL_CHECK(glTranslated(x, y, 0));

    GL_CHECK(glListBase(base - 32 + (128 * 1)));

    GL_CHECK(glCallLists((GLsizei) strlen(text), GL_BYTE, text));
    */
  };

  font_texture_->Bind(func);
}

void Video::Init2DScene(int width, int height) {
  GL_CHECK(glDisable(GL_DEPTH_TEST));
  GL_CHECK(glDisable(GL_CULL_FACE));
  // GL_CHECK(glDisable(GL_LIGHTING));
  // GL_CHECK(glDisable(GL_COLOR_MATERIAL));

  // GL_CHECK(glMatrixMode(GL_PROJECTION));

  // ortho2D(0.0f, width, height, 0.0f);

  // GL_CHECK(glMatrixMode(GL_MODELVIEW));

  // GL_CHECK(glLoadIdentity());
}

void Video::Init3DScene(int width, int height) {
  GL_CHECK(glEnable(GL_DEPTH_TEST));
  GL_CHECK(glEnable(GL_CULL_FACE));
  // GL_CHECK(glEnable(GL_LIGHTING));

  GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));

  // GL_CHECK(glMatrixMode(GL_PROJECTION));

  // perspectiveGL(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);

  // GL_CHECK(glMatrixMode(GL_MODELVIEW));

  // GL_CHECK(glLoadIdentity());

  // glm::mat4 cam = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
  //   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  // GL_CHECK(glLoadMatrixf(glm::value_ptr(cam)));

  // GLfloat lmodel_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  // GL_CHECK(glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient));

  // GLfloat light_ambient[] = { 0.5f, 0.0f, 0.5f, 0.0f };
  // GL_CHECK(glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient));

  // GLfloat light_diffuse[] = { 0.5f, 0.0f, 0.5f, 0.0f };
  // GL_CHECK(glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse));

  // GLfloat light_position[] = { 0.f, 0.0f, 100.0f, 0.0f };
  // GL_CHECK(glLightfv(GL_LIGHT0, GL_POSITION, light_position));

  // GL_CHECK(glClearColor(0.2f, 0.0f, 0.2f, 0.0));

  // GL_CHECK(glEnable(GL_LIGHT0));

  // GL_CHECK(glEnable(GL_COLOR_MATERIAL));
  // GL_CHECK(glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE));
}

glm::vec3 Video::GetNormal(const glm::vec3 v0, const glm::vec3 v1,
                           const glm::vec3 v2) {
  return glm::normalize(glm::cross(v2 - v0, v1 - v0));
}

void Video::DrawTexture(int x, int y, int w, int h,
    std::shared_ptr<Texture> const &texture, GLfloat yamount) {
  glm::i32vec2 v0(x, y);
  glm::i32vec2 v1(x, y + h);
  glm::i32vec2 v2(x + w, y);
  glm::i32vec2 v3(x + w, y + h);

  texture->Bind();

  /*
  GL_CHECK(glLoadIdentity());

  glBegin(GL_TRIANGLE_STRIP);
  
  glTexCoord2f(0.0f, yamount);
  glVertex2iv(glm::value_ptr(v0));

  glTexCoord2f(0.0f, 1.0f);
  glVertex2iv(glm::value_ptr(v1));

  glTexCoord2f(1.0f, yamount);
  glVertex2iv(glm::value_ptr(v2));

  glTexCoord2f(1.0f, 1.0f);
  glVertex2iv(glm::value_ptr(v3));
  
  GL_CHECK(glEnd());
  */
}
