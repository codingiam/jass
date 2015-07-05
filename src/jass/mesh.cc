// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/mesh.h"

#include <boost/filesystem.hpp>

#include <cstdio>
#include <string>

Mesh::Mesh() {
  *this->path_ = 0;
  this->filename_ = NULL;
  this->mesh_ = 0;
}

Mesh::~Mesh() {
  materials_.clear();

  for (unsigned int i = 1; i <= verticies_.size(); i++) {
    delete[] verticies_[i - 1];
  }

  for (unsigned int i = 1; i <= tcoords_.size(); i++) {
    delete[] tcoords_[i - 1];
  }

  for (unsigned int i = 1; i <= normals_.size(); i++) {
    delete[] normals_[i - 1];
  }

  if (mesh_) { GL_CHECK(glDeleteLists(mesh_, 1)); }
}

void Mesh::LoadMeshObj(const char* filename, const char *path) {
  if (mesh_) return;

  FILE* fp = fopen((boost::filesystem::path(path) /= filename).
    string().c_str(), "r");
  if (!fp) return;

  strncpy(this->path_, path, PATH_LENGTH - 1);
  this->path_[PATH_LENGTH - 1] = 0;

  this->filename_ = filename;

//  char *cmd, *params, *trimer;

  LoadMaterialObj("spaceship.mtl");
  /*
  GL_CHECK(this->mesh_ = glGenLists(1));

  GL_CHECK(glNewList(mesh_, GL_COMPILE));

  glBegin(GL_TRIANGLES);

  char buffer[100];

  while (!feof(fp)) {
    *buffer = 0; fgets(buffer, 100, fp);
    cmd = params = trimer = buffer;

    while (*trimer >= 32) trimer++; *trimer = 0;

    while ((*params) && (*params != ' ')) params++;

    cmd[params - buffer] = 0; params++;

    if (*cmd) ProcessCmdObj(cmd, params);
  }

  GL_CHECK(glEnd());

  GL_CHECK(glEndList());
  */

  fclose(fp);
}

void Mesh::ProcessCmdObj(char *cmd, char *params) {
  /*
  if (strcmp(cmd, "mtllib") == 0) {
    loadMaterialObj(params);
    return ;
  }*/

  if (strcmp(cmd, "v") == 0) {
    float *vertex = new float[3];
    memset(vertex, 0, sizeof(float[3]));
    if (sscanf(params, "%f %f %f", &vertex[0], &vertex[1], &vertex[2]) != EOF) {
      verticies_.push_back(vertex);
    }

    return;
  }

  if (strcmp(cmd, "vt") == 0) {
    GLdouble *tcoord = new GLdouble[2];
    if (sscanf(params, "%lf %lf", &tcoord[0], &tcoord[1]) != EOF) {
      tcoord[1] = 1.0f - tcoord[1];
      tcoords_.push_back(tcoord);
    }

    return;
  }

  if (strcmp(cmd, "vn") == 0) {
    float *normal = new float[3];
    if (sscanf(params, "%f %f %f", &normal[0], &normal[1], &normal[2]) != EOF) {
      normals_.push_back(normal);
    }

    return;
  }

  if (strcmp(cmd, "f") == 0) {
    ProcessFace(params);
    return;
  }

/*
  if (strcmp(cmd, "usemtl") == 0) {
    for(unsigned int i = 1; i <= materials.size(); i++) {
      Material* mat = materials[i - 1];

      if (strcmp(mat->getName(), params) == 0) {
        mat->useMaterial();

        break;
      }
    }

    return ;
  }
*/

  // std::cout << cmd << "(" << params << ")" << std::endl;
/*
  v Geometric vertices
  vt Texture vertices
  vn Vertex normals

  f Face

  g Group name
  s Smoothing group

  usemtl Material name
  mtllib Material library
*/
}

void Mesh::LoadMaterialObj(const char *filename) {
  auto mat = std::make_shared<Material>();

  mat->LoadMaterial(filename, path_);

  materials_.push_back(mat);
}

void Mesh::Display() {
  if (!mesh_) {
    std::cout << "mesh not loaded" << std::endl;

    return;
  }

  for (unsigned int i = 1; i <= materials_.size(); i++) {
    materials_[i - 1]->UseMaterial();
    if (i == 1) {
      break;
    }
  }

  GL_CHECK(glCallList(mesh_));
}

void Mesh::ProcessFace(char *face) {
  unsigned int v1, t1, n1;
  unsigned int v2, t2, n2;
  unsigned int v3, t3, n3;

  if (sscanf(face, "%u/%u/%u %u/%u/%u %u/%u/%u",
      &v1, &t1, &n1,
      &v2, &t2, &n2,
      &v3, &t3, &n3) != EOF) {
    GL_CHECK(glNormal3fv(normals_[--n1]));
    GL_CHECK(glTexCoord2dv(tcoords_[--t1]));
    GL_CHECK(glVertex3fv(verticies_[--v1]));

    GL_CHECK(glNormal3fv(normals_[--n2]));
    GL_CHECK(glTexCoord2dv(tcoords_[--t2]));
    GL_CHECK(glVertex3fv(verticies_[--v2]));

    GL_CHECK(glNormal3fv(normals_[--n3]));
    GL_CHECK(glTexCoord2dv(tcoords_[--t3]));
    GL_CHECK(glVertex3fv(verticies_[--v3]));
  }
}
