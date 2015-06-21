// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/video.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sstream>
#include <cmath>
#include <string>

#include "jass/application.h"
#include "jass/image.h"

static void perspectiveGL(GLdouble fovY, GLdouble aspect,
                          GLdouble zNear, GLdouble zFar) {
  glm::mat4 persp = glm::perspective(fovY, aspect, zNear, zFar);
  glLoadMatrixf(glm::value_ptr(persp));
}

static void ortho2D(GLdouble left, GLdouble right,
                    GLdouble bottom, GLdouble top) {
  glm::mat4 ortho = glm::ortho(left, right, bottom, top);
  glLoadMatrixf(glm::value_ptr(ortho));
}

Video::Video() {
  ilInit();
  fontTexture = 0;
  base = 0;
  zpos = 1.0f;
}

boost::shared_ptr<Image> Video::loadImage(boost::filesystem::path const &path) {
  boost::shared_ptr<Image> image = boost::shared_ptr<Image>(new Image());
  if (!image->loadImage(path.string())) {
    boost::format message =
      boost::format("Could not load image: %s") % path.string();
    throw std::runtime_error(message.str());
  }
  return image;
}

void Video::makeTexture(boost::shared_ptr<Image> const &image,
                        GLuint *texture) {
  glGenTextures(1, texture);

  auto func = [texture] (GLubyte *pixels, GLuint width, GLuint height) {
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
      0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  };

  image->withData(func);
}

void Video::InitFont() {
  if ((fontTexture) || (base))
    return;

  boost::shared_ptr<Image> textura = loadImage("data/fonturi/font.png");
  makeTexture(textura, &fontTexture);

  float cx = 0, cy = 0;

  base = glGenLists(256);
  glBindTexture(GL_TEXTURE_2D, fontTexture);

  for (int loop = 0; loop < 256; loop++) {
    glNewList(base + loop, GL_COMPILE);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(cx / 256, cy / 256);
    glVertex2i(0, 0);

    glTexCoord2f(cx / 256, (cy + 16) / 256);
    glVertex2i(0, 16);

    glTexCoord2f((cx + 16) / 256, cy / 256);
    glVertex2i(16, 0);

    glTexCoord2f((cx + 16) / 256, (cy + 16) / 256);
    glVertex2i(16, 16);
    glEnd();

    glTranslated(10, 0, 0);
    glEndList();

    cx += 16;
    if (fabs(cx - 256) <= .1f) {
      cx = 0;
      cy += 16;
    }
  }
}

void Video::print(GLint x, GLint y, const char *text, int set) {
  glBindTexture(GL_TEXTURE_2D, fontTexture);

  glLoadIdentity();

  glTranslated(x, y, 0);

  glListBase(base - 32 + (128 * 1));

  glCallLists((GLsizei) strlen(text), GL_BYTE, text);
}

void Video::init2DScene(int width, int height) {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);

  glMatrixMode(GL_PROJECTION);

  ortho2D(0.0f, width, height, 0.0f);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
}

void Video::init3DScene(int width, int height) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);

  glClear(GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);

  perspectiveGL(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  glm::mat4 cam = glm::lookAt(glm::vec3(0.0f, 0.0f, zpos),
    glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glLoadMatrixf(glm::value_ptr(cam));

  GLfloat lmodel_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  GLfloat light_ambient[] = { 0.5f, 0.0f, 0.5f, 0.0f };
  GLfloat light_diffuse[] = { 0.5f, 0.0f, 0.5f, 0.0f };

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

  GLfloat light_position[] = { 0.f, 0.0f, 100.0f, 0.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glClearColor(0.2f, 0.0f, 0.2f, 0.0);

  glEnable(GL_LIGHT0);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

glm::vec3 Video::getNormal(const glm::vec3 v0, const glm::vec3 v1,
                           const glm::vec3 v2) {
  return glm::normalize(glm::cross(v2 - v0, v1 - v0));
}

void Video::drawTexture(int x, int y, int w, int h, GLuint texture,
    GLfloat yamount) {
  glm::i32vec2 v0(x, y);
  glm::i32vec2 v1(x, y + h);
  glm::i32vec2 v2(x + w, y);
  glm::i32vec2 v3(x + w, y + h);

  glBindTexture(GL_TEXTURE_2D, texture);

  glBegin(GL_TRIANGLE_STRIP);
  glTexCoord2f(0.0f, yamount);
  glVertex2iv(glm::value_ptr(v0));

  glTexCoord2f(0.0f, 1.0f);
  glVertex2iv(glm::value_ptr(v1));

  glTexCoord2f(1.0f, yamount);
  glVertex2iv(glm::value_ptr(v2));

  glTexCoord2f(1.0f, 1.0f);
  glVertex2iv(glm::value_ptr(v3));
  glEnd();
}

Video::~Video() {
  ilShutDown();

  if (base)
    glDeleteLists(base, 256);
  if (fontTexture)
    glDeleteTextures(1, &fontTexture);
}

void Video::plusZpos() {
  this->zpos -= 0.1f;
}

void Video::minusZpos() {
  this->zpos += 0.1f;
}
