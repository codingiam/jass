//
//  buffer_object.cpp
//  jass
//
//  Created by Doru Budai on 13/07/15.
//  Copyright (c) 2015 Doru Budai. All rights reserved.
//

#include "buffer_object.h"

BufferObject::BufferObject() {
  this->vbo_id_ = 0;
}

BufferObject::~BufferObject() {
  if (vbo_id_) {
    GL_CHECK(glDeleteBuffers(1, &vbo_id_));
    this->vbo_id_ = 0;
  }
}

void BufferObject::Create() {
  GL_CHECK(glGenBuffers(1, &vbo_id_));
  // glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
}

bool BufferObject::Bind(std::function<void()> const &func) {
  if (!vbo_id_) {
    return false;
  }

  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo_id_));

  func();

  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

  return true;
}
