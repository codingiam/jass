// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/material.h"

#include <cstdio>

#include "jass/video.h"

Material::Material() {
  *name_ = 0;
  *path_ = 0;
  filename_ = NULL;
  format_ = 0;
  matTexture_ = 0;
}

Material::~Material() {
  if (matTexture_) glDeleteTextures(1, &matTexture_);
}

void Material::loadMaterial(const char *filename, const char *path) {
  char buffer[100];

  _snprintf(buffer, sizeof(buffer), "%s%s\0", path, filename);

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

    if (*cmd) processCmdMat(cmd, params);
  }

  fclose(fp);
}

void Material::processCmdMat(char *cmd, char *params) {
  if (strcmp(cmd, "newmtl") == 0) {
    _snprintf(name_, sizeof(name_), "%s", params);

    return;
  }

  if (strcmp(cmd, "Ka") == 0) {
    sscanf(params, "%f %f %f", &matAmbient_[0], &matAmbient_[1],
      &matAmbient_[2]);
    format_ |= MAT_AMBIENT;

    return;
  }

  if (strcmp(cmd, "Kd") == 0) {
    sscanf(params, "%f %f %f", &matDiffuse_[0], &matDiffuse_[1],
      &matDiffuse_[2]);
    format_ |= MAT_DIFFUSE;

    return;
  }

  if (strcmp(cmd, "Ks") == 0) {
    sscanf(params, "%f %f %f",
      &matSpecular_[0], &matSpecular_[1], &matSpecular_[2]);
    format_ |= MAT_SPECULAR;

    return;
  }

  if (strcmp(cmd, "Ns") == 0) {
    sscanf(params, "%f", &matShiness_);
    format_ |= MAT_SHINESS;

    return;
  }

  if (strcmp(cmd, "map_Kd") == 0) {
    char buffer[100];

    Video* video = Video::GetVideo();

    _snprintf(buffer, sizeof(buffer), "%s%s", path_, params);

    boost::shared_ptr<Image> tmp = video->loadImage(buffer);
    video->makeTexture(tmp, &matTexture_);

    format_ |= MAT_TEXTURE;
  }
}

void Material::useMaterial() {
  if (format_ & MAT_TEXTURE)
    glBindTexture(GL_TEXTURE_2D, matTexture_);

  if (format_ & MAT_AMBIENT)
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient_);
  if (format_ & MAT_DIFFUSE)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse_);
  if (format_ & MAT_SPECULAR)
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular_);
  if (format_ & MAT_SHINESS)
    glMaterialfv(GL_FRONT, GL_SHININESS, &matShiness_);
}
