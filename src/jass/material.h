// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_MATERIAL_H_
#define JASS_MATERIAL_H_
#pragma once

#include "jass/jass.h"

#define PATH_LENGTH 100

class Texture;

class Material : private boost::noncopyable {
 public:
  Material();
  ~Material();

  void LoadMaterial(const char* filename, const char* path);
  const char* GetName() { return name_; }
  void UseMaterial();

  std::shared_ptr<Texture> mat_texture_;

 private:
  enum  { MAT_AMBIENT = 1, MAT_DIFFUSE = 2, MAT_SPECULAR = 4, MAT_SHINESS = 8,
    MAT_TEXTURE = 16 };

  void ProcessCmdMat(char *cmd, char *params);

  char path_[PATH_LENGTH];
  const char* filename_;
  char name_[50];

  GLushort format_;

  GLfloat mat_ambient_[3], mat_diffuse_[3], mat_specular_[3], mat_shiness_;
};

#endif  // JASS_MATERIAL_H_
