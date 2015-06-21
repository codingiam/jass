// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/mesh_reader.h"

#include <string>
#include <fstream>

MeshReader::MeshReader(const char *filename, const char* path ) {
  std::string openfile = path;
  openfile += filename;

  fp = fopen(openfile.c_str(), "r");
}

MeshReader::~MeshReader() {
  if (fp) fclose( fp );
}
