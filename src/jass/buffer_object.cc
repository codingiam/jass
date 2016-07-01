//
//  buffer_object.cpp
//  jass
//
//  Created by Doru Budai on 13/07/15.
//  Copyright (c) 2015 Doru Budai. All rights reserved.
//

#include "buffer_object.h"

BufferObject::BufferObject(const GLenum target) {
  this->target_ = target;
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
  // glBufferData(target_, size, NULL, GL_STATIC_DRAW);
}

bool BufferObject::Bind(std::function<void(GLenum)> const &func) {
  if (!vbo_id_) {
    return false;
  }

  GL_CHECK(glBindBuffer(target_, vbo_id_));

  func(target_);

  GL_CHECK(glBindBuffer(target_, 0));

  return true;
}
