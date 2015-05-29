// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/mesh.h"

#include <iostream>
#include <cstdio>

Mesh::Mesh() {
  *path = 0;
  filename = NULL;
  mesh = 0;
}

Mesh::~Mesh() {
  for(unsigned int i = 1; i <= materials.size(); i++) {
    delete materials[i - 1];
  }

  for(unsigned int i = 1; i <= verticies.size(); i++) {
    delete[] verticies[i - 1];
  }

  for(unsigned int i = 1; i <= tcoords.size(); i++) {
    delete[] tcoords[i - 1];
  }

  for(unsigned int i = 1; i <= normals.size(); i++) {
    delete[] normals[i - 1];
  }

  if (mesh) glDeleteLists( mesh, 1 );
}

void Mesh::loadMeshObj(char* filename, const char *path) {
  char buffer[100];
      
  sprintf( buffer, "%s%s", path, filename );

  FILE* fp = fopen( buffer, "r" );
  if ((!fp) || (mesh)) return ;

  strncpy(this->path, path, PATH_LENGTH - 1);
  this->path[PATH_LENGTH - 1] = 0;

  this->filename = filename;

  char *cmd, *params, *trimer;

  loadMaterialObj( "spaceship.mtl" );

  mesh = glGenLists( 1 );

  glNewList( mesh, GL_COMPILE );

  glBegin( GL_TRIANGLES );

  while( !feof( fp ) ) {
    *buffer = 0; fgets( buffer, 100, fp );
    cmd = params = trimer = buffer;

    while( *trimer >= 32 ) trimer++; *trimer = 0;

    while( (*params) && (*params != ' ')) params++;
    
    cmd[params - buffer] = 0; params++;

    if (*cmd) processCmdObj(cmd, params);
  }

  glEnd();

  glEndList();

  fclose(fp);
}

void Mesh::processCmdObj(char *cmd, char *params) {
  /*
  if (strcmp( cmd, "mtllib" ) == 0) {
    loadMaterialObj( params );
    return ;
  }*/
  
  if (strcmp(cmd, "v") == 0) {
    float *vertex = new float[3];
    memset(vertex, 0, sizeof(float[3]));
    sscanf( params, "%f %f %f", &vertex[0], &vertex[1], &vertex[2] );

    verticies.push_back( vertex );

    return ;
  }

  if (strcmp(cmd, "vt") == 0) {
    GLdouble *tcoord = new GLdouble[2];
    sscanf( params, "%lf %lf", &tcoord[0], &tcoord[1] );

    tcoord[1] = 1.0f - tcoord[1];

    tcoords.push_back( tcoord );

    return ;
  }

  if (strcmp(cmd, "vn") == 0) {
    float *normal = new float[3];
    sscanf( params, "%f %f %f", &normal[0], &normal[1], &normal[2] );

    normals.push_back( normal );

    return ;
  }

  if (strcmp(cmd, "f") == 0) {
    processFace( params );
    
    return ;
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

  //std::cout << cmd << "(" << params << ")" << std::endl;
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

void Mesh::loadMaterialObj(char *filename) {
  Material* mat = new Material();

  mat->loadMaterial( filename, path );

  materials.push_back( mat );
}

void Mesh::display() {
  if (!mesh) {
    std::cout << "mesh not loaded" << std::endl;

    return ;
  }

  for(unsigned int i = 1; i <= materials.size(); i++) {
    Material* mat = materials[i - 1];
    mat->useMaterial();
    break;
  }

  glCallList( mesh );
}

void Mesh::processFace(char *face) {
  unsigned int v1, t1, n1; 
  unsigned int v2, t2, n2;
  unsigned int v3, t3, n3;

  sscanf( face, "%u/%u/%u %u/%u/%u %u/%u/%u",
    &v1, &t1, &n1,
    &v2, &t2, &n2,
    &v3, &t3, &n3);

  glNormal3fv( normals[--n1] );
  glTexCoord2dv( tcoords[--t1] );
  glVertex3fv( verticies[--v1] );

  glNormal3fv( normals[--n2] );
  glTexCoord2dv( tcoords[--t2] );
  glVertex3fv( verticies[--v2] );

  glNormal3fv( normals[--n3] );
  glTexCoord2dv( tcoords[--t3] );
  glVertex3fv( verticies[--v3] );
}
