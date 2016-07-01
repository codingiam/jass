// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/gl/vertex_array_object.h"

namespace GL {

VertexArrayObject::VertexArrayObject() {
  this->vao_id_ = 0;
}

VertexArrayObject::~VertexArrayObject() {
  if (vao_id_) {
    glDeleteVertexArrays(1, &vao_id_);
    this->vao_id_ = 0;
  }
}

void VertexArrayObject::Create() {
  glGenVertexArrays(1, &vao_id_);
}

bool VertexArrayObject::Bind(std::function<void()> const &func) {
  if (!vao_id_) {
    return false;
  }

  glBindVertexArray(vao_id_);

  func();

  glBindVertexArray(0);

  return true;
}

}  // namespace GL
