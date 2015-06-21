// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_MESHREADER_H_
#define JASS_SRC_JASS_MESHREADER_H_
#pragma once

#include "jass/jass.h"

class MeshReader : boost::noncopyable {
 public:
  explicit MeshReader(const char* filename, const char* path = "./");
  ~MeshReader();

 private:
  FILE* fp;
};

#endif  // JASS_SRC_JASS_MESHREADER_H_
