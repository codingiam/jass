// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_MESH_H_
#define JASS_SRC_JASS_MESH_H_
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
  void loadMaterialObj(char* filename);
  void processFace(char* face);

  char path[PATH_LENGTH];
  const char* filename;

  std::vector<Material*> materials;
  std::vector<GLfloat*> verticies;
  std::vector<GLdouble*> tcoords;
  std::vector<GLfloat*> normals;

  GLuint mesh;
};

#endif  // JASS_SRC_JASS_MESH_H_
