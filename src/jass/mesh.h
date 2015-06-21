// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_MESH_H_
#define JASS_MESH_H_
#pragma once

#include <vector>

#include "jass/material.h"

#define PATH_LENGTH 100

class Mesh : boost::noncopyable {
 public:
  Mesh();
  ~Mesh();

  void loadMeshObj(const char* filename, const char* path = "./");
  void display();

 private:
  void processCmdObj(char* cmd, char* params);
  void loadMaterialObj(const char* filename);
  void processFace(char* face);

  char path_[PATH_LENGTH];
  const char* filename_;

  std::vector<Material*> materials_;
  std::vector<GLfloat*> verticies_;
  std::vector<GLdouble*> tcoords_;
  std::vector<GLfloat*> normals_;

  GLuint mesh_;
};

#endif  // JASS_MESH_H_
