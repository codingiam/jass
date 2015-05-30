// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/video.h"

#include <iostream>
#include <sstream>
#include <cmath>

#include "jass/application.h"

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar ) {
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    
    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void ortho2D( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
    glOrtho( left, right, bottom, top, -1, 1 );
}

Video::Video() {
  fontTexture = 0;
  base = 0;
}

SDL_Surface* Video::loadTexture(char* name) {
  char buffer[100];
  int i = 0;
  for ( ; i < 100 && *(name + i) != '\0'; i++) {
    char tmp = *(name + i);
    if (tmp == '\\')
      tmp = '/';
    buffer[i] = tmp;
  }
  buffer[i] = '\0';

  printf("Incarc textura: %s\n", buffer);

  SDL_Surface* textura = IMG_Load(buffer);

  if ((!textura) || (textura->format->BitsPerPixel <= 8)) {
    if (!textura) {
      throw(std::runtime_error("Nu am putut incarca textura.") );
    }

        std::ostringstream oss(std::ostringstream::out);
        oss << "Numar de BPP invalid : " << textura->format->BitsPerPixel;
//    char message[100];
//    sprintf(message, "Numar de BPP invalid : %d",
//        textura->format->BitsPerPixel);
    SDL_FreeSurface(textura);

        throw(std::runtime_error(oss.str()));
  }

  std::cout << name << " = " << (int) textura->format->BitsPerPixel << "bpp"
      << std::endl;

  return textura;
}

void Video::makeTexture(SDL_Surface* surface, GLuint &texture) {
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  GLenum format = GL_RGB;
  if (surface->format->BytesPerPixel == 4)
    format = GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w,
      surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
}

void Video::InitFont() {
  if ((fontTexture) || (base))
    return;

  SDL_Surface* textura = loadTexture("data\\fonturi\\font.png");
  makeTexture(textura, fontTexture);
  SDL_FreeSurface(textura);

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

void Video::print(GLint x, GLint y, const char *string, int set) {
  glBindTexture(GL_TEXTURE_2D, fontTexture);

  glLoadIdentity();

  glTranslated(x, y, 0);

  glListBase(base - 32 + (128 * 1));

  glCallLists((GLsizei) strlen(string), GL_BYTE, string);
}

void Video::init2DScene(int width, int height) {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

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
  glLoadIdentity();

  perspectiveGL(45.0f, (GLfloat) width / (GLfloat) height, 1.0f, 300.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

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

void Video::getNormal(vertex3f v0, vertex3f v1, vertex3f v2, vertex3f &normal) {
  GLfloat x01 = v0[0] - v1[0];
  GLfloat y01 = v0[1] - v1[1];
  GLfloat z01 = v0[2] - v1[2];

  GLfloat x02 = v0[0] - v2[0];
  GLfloat y02 = v0[1] - v2[1];
  GLfloat z02 = v0[2] - v2[2];

  GLfloat cpx = (y01 * z02) - (z01 * y02);
  GLfloat cpy = (z01 * x02) - (x01 * z02);
  GLfloat cpz = (x01 * y02) - (y01 * x02);

  GLfloat r = (float) sqrt(cpx * cpx + cpy * cpy + cpz * cpz);

  normal[0] = cpx / r;
  normal[1] = cpy / r;
  normal[2] = cpz / r;
}

void Video::drawTexture(int x, int y, int w, int h, GLuint texture,
    GLfloat yamount) {
  vertex2i v0 = { x, y };
  vertex2i v1 = { x, y + h };
  vertex2i v2 = { x + w, y };
  vertex2i v3 = { x + w, y + h };

  glBindTexture(GL_TEXTURE_2D, texture);

  glBegin(GL_TRIANGLE_STRIP);
  glTexCoord2f(0.0f, yamount);
  glVertex2iv(v0);

  glTexCoord2f(0.0f, 1.0f);
  glVertex2iv(v1);

  glTexCoord2f(1.0f, yamount);
  glVertex2iv(v2);

  glTexCoord2f(1.0f, 1.0f);
  glVertex2iv(v3);
  glEnd();
}

Video::~Video() {
  if (base)
    glDeleteLists(base, 256);
  if (fontTexture)
    glDeleteTextures(1, &fontTexture);
}
