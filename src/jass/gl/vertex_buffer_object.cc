// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/gl/vertex_buffer_object.h"

namespace GL {

VertexBufferObject::VertexBufferObject(const GLenum target) {
  this->target_ = target;
  this->vbo_id_ = 0;
}

VertexBufferObject::~VertexBufferObject() {
  if (vbo_id_) {
    glDeleteBuffers(1, &vbo_id_);
    this->vbo_id_ = 0;
  }
}

void VertexBufferObject::Create() {
  glGenBuffers(1, &vbo_id_);
}

bool VertexBufferObject::Bind(std::function<void(GLenum)> const &func) {
  if (!vbo_id_) {
    return false;
  }

  glBindBuffer(target_, vbo_id_);

  func(target_);

  glBindBuffer(target_, 0);

  return true;
}

}  // namespace GL
