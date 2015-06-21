// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_MATERIAL_H_
#define JASS_SRC_JASS_MATERIAL_H_
#pragma once

#include "jass/jass.h"

#define PATH_LENGTH 100

class Material : boost::noncopyable {
 public:
  Material();
  ~Material();

  void loadMaterial(const char* filename, const char* path = "./");
  const char* getName() { return name_; }
  void useMaterial();

  GLuint matTexture_;

 private:
  enum  { MAT_AMBIENT = 1, MAT_DIFFUSE = 2, MAT_SPECULAR = 4, MAT_SHINESS = 8,
    MAT_TEXTURE = 16 };

  void processCmdMat(char* cmd, char* params);

  char path_[PATH_LENGTH];
  const char* filename_;
  char name_[50];

  GLushort format_;

  GLfloat matAmbient_[3], matDiffuse_[3], matSpecular_[3], matShiness_;
};

#endif  // JASS_SRC_JASS_MATERIAL_H_
