// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef __jass__buffer_object__
#define __jass__buffer_object__

#include <GL/glew.h>

#include <functional>

namespace GL {

class VertexBufferObject {
 public:
  VertexBufferObject(const VertexBufferObject &) = delete;
  VertexBufferObject & operator=(const VertexBufferObject &) = delete;

  explicit VertexBufferObject(const GLenum target);
  ~VertexBufferObject(void);

  void Create(void);

  bool Bind(std::function<void(GLenum)> const &func);
 private:
  GLenum target_;
  GLuint vbo_id_;
};

}  // namespace GL

#endif /* defined(__jass__buffer_object__) */
