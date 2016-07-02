// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_GL_VERTEX_ARRAY_OBJECT_H_
#define JASS_GL_VERTEX_ARRAY_OBJECT_H_

#include <GL/glew.h>

#include <functional>

namespace GL {

class VertexArrayObject {
 public:
  VertexArrayObject(const VertexArrayObject &) = delete;
  VertexArrayObject & operator=(const VertexArrayObject &) = delete;

  VertexArrayObject(void);
  ~VertexArrayObject(void);

  void Create(void);

  bool Bind(std::function<void()> const &func);
 private:
  GLuint vao_id_;
};

}  // namespace GL

#endif  // JASS_GL_VERTEX_ARRAY_OBJECT_H_
