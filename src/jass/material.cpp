// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/material.h"

#include <cstdio>

#include "jass/video.h"

Material::Material() {
  *name = 0;
  *path = 0;
  filename = NULL;
  format = 0;
  matTexture = 0;
}

Material::~Material() {
  if (matTexture) glDeleteTextures( 1, &matTexture );
}

void Material::loadMaterial(char *filename, const char *path) {
  char buffer[100];
  
  sprintf( buffer, "%s%s", path, filename );

  FILE* fp = fopen( buffer, "r" );
  if (!fp) return ;

  strncpy(this->path, path, PATH_LENGTH - 1);
  this->path[PATH_LENGTH - 1] = 0;

  this->filename = filename;

  char *cmd, *params, *trimer;

  while( !feof( fp ) ) {
    *buffer = 0; fgets( buffer, 100, fp );
    cmd = params = trimer = buffer;

    while( *trimer >= 32 ) trimer++; *trimer = 0;

    while( (*params) && (*params != ' ')) params++;
    
    cmd[params - buffer] = 0; params++;

    if (*cmd) processCmdMat(cmd, params);
  }

  fclose(fp);
}

void Material::processCmdMat(char *cmd, char *params) {
  if (strcmp( cmd, "newmtl" ) == 0) {
    sprintf( name, "%s", params );

    return ;
  }

  if (strcmp( cmd, "Ka" ) == 0) {
    sscanf( params, "%f %f %f", &matAmbient[0], &matAmbient[1], &matAmbient[2] );
    format |= MAT_AMBIENT;

    return ;
  }

  if (strcmp( cmd, "Kd" ) == 0) {
    sscanf( params, "%f %f %f", &matDiffuse[0], &matDiffuse[1], &matDiffuse[2] );
    format |= MAT_DIFFUSE;

    return ;
  }

  if (strcmp( cmd, "Ks" ) == 0) {
    sscanf( params, "%f %f %f", &matSpecular[0], &matSpecular[1], &matSpecular[2] );
    format |= MAT_SPECULAR;

    return ;
  }

  if (strcmp( cmd, "Ns" ) == 0) {
    sscanf( params, "%f", &matShiness );
    format |= MAT_SHINESS;

    return ;
  }

  if (strcmp( cmd, "map_Kd" ) == 0) {
    char buffer[100];

    Video* video = Video::GetVideo();
    
    sprintf( buffer, "%s%s", path, params );

    SDL_Surface * tmp = video->loadTexture( buffer );
    video->makeTexture( tmp, matTexture );
    SDL_FreeSurface( tmp );

    format |= MAT_TEXTURE;
  }
}

void Material::useMaterial() {
  if (format & MAT_TEXTURE)
    glBindTexture( GL_TEXTURE_2D, matTexture );

  if (format & MAT_AMBIENT)
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
  if (format & MAT_DIFFUSE)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
  if (format & MAT_SPECULAR)
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  if (format & MAT_SHINESS)
    glMaterialfv(GL_FRONT, GL_SHININESS, &matShiness);
}
