//
//  vertex_array_object.cpp
//  jass
//
//  Created by Doru Budai on 13/07/15.
//  Copyright (c) 2015 Doru Budai. All rights reserved.
//

#include "vertex_array_object.h"

VertexArrayObject::VertexArrayObject() {
  this->vao_id_ = 0;
}

VertexArrayObject::~VertexArrayObject() {
  if (vao_id_) {
    GL_CHECK(glDeleteVertexArrays(1, &vao_id_));
    this->vao_id_ = 0;
  }
}

void VertexArrayObject::Create() {
  GL_CHECK(glGenVertexArrays(1, &vao_id_));
}

bool VertexArrayObject::Bind(std::function<void()> const &func) {
  if (!vao_id_) {
    return false;
  }

  GL_CHECK(glBindVertexArray(vao_id_));

  func();

  GL_CHECK(glBindVertexArray(0));

  return true;
}