// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_MESH_H_
#define JASS_MESH_H_
#pragma once

#include <vector>

#include "jass/material.h"

#define PATH_LENGTH 100

class Video;

class Mesh : boost::noncopyable {
 public:
  Mesh();
  ~Mesh();

  void LoadMeshObj(const char* filename, const char* path);
  void Display();

 private:
  void ProcessCmdObj(char* cmd, char* params);
  void LoadMaterialObj(const char* filename);
  void ProcessFace(char* face);

  char path_[PATH_LENGTH];
  const char* filename_;

  std::vector<Material*> materials_;
  std::vector<GLfloat*> verticies_;
  std::vector<GLdouble*> tcoords_;
  std::vector<GLfloat*> normals_;

  GLuint mesh_;
};

#endif  // JASS_MESH_H_
