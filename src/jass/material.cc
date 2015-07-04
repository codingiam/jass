// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/material.h"

#include <cstdio>

#include "jass/video.h"

#include "jass/image.h"
#include "jass/texture.h"

Material::Material() {
  *this->name_ = 0;
  *this->path_ = 0;
  this->filename_ = NULL;
  this->format_ = 0;
}

Material::~Material() {
  mat_texture_.reset();
}

void Material::LoadMaterial(const char *filename, const char *path) {
  char buffer[100];

  snprintf(buffer, sizeof(buffer), "%s%s", path, filename);

  FILE* fp = fopen(buffer, "r");
  if (!fp) return;

  strncpy(this->path_, path, PATH_LENGTH - 1);
  this->path_[PATH_LENGTH - 1] = 0;

  this->filename_ = filename;

  char *cmd, *params, *trimer;

  while (!feof(fp)) {
    *buffer = 0; fgets(buffer, 100, fp);
    cmd = params = trimer = buffer;

    while (*trimer >= 32) trimer++; *trimer = 0;

    while ((*params) && (*params != ' ')) params++;

    cmd[params - buffer] = 0; params++;

    if (*cmd) ProcessCmdMat(cmd, params);
  }

  fclose(fp);
}

void Material::ProcessCmdMat(char *cmd, char *params) {
  if (strcmp(cmd, "newmtl") == 0) {
    snprintf(name_, sizeof(name_), "%s", params);

    return;
  }

  if (strcmp(cmd, "Ka") == 0) {
    sscanf(params, "%f %f %f", &mat_ambient_[0], &mat_ambient_[1],
      &mat_ambient_[2]);
    format_ |= MAT_AMBIENT;

    return;
  }

  if (strcmp(cmd, "Kd") == 0) {
    sscanf(params, "%f %f %f", &mat_diffuse_[0], &mat_diffuse_[1],
      &mat_diffuse_[2]);
    format_ |= MAT_DIFFUSE;

    return;
  }

  if (strcmp(cmd, "Ks") == 0) {
    sscanf(params, "%f %f %f",
      &mat_specular_[0], &mat_specular_[1], &mat_specular_[2]);
    format_ |= MAT_SPECULAR;

    return;
  }

  if (strcmp(cmd, "Ns") == 0) {
    sscanf(params, "%f", &mat_shiness_);
    format_ |= MAT_SHINESS;

    return;
  }

  if (strcmp(cmd, "map_Kd") == 0) {
    char buffer[100];

    snprintf(buffer, sizeof(buffer), "%s%s", path_, params);

    std::shared_ptr<Image> image = Image::MakeImage(buffer);
    this->mat_texture_ = Texture::MakeTexture(image);

    format_ |= MAT_TEXTURE;
  }
}

void Material::UseMaterial() {
  if (format_ & MAT_TEXTURE)
    mat_texture_->Bind();
  if (format_ & MAT_AMBIENT)
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_);
  if (format_ & MAT_DIFFUSE)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_);
  if (format_ & MAT_SPECULAR)
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_);
  if (format_ & MAT_SHINESS)
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shiness_);
}
