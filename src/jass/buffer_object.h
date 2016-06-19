//
//  buffer_object.h
//  jass
//
//  Created by Doru Budai on 13/07/15.
//  Copyright (c) 2015 Doru Budai. All rights reserved.
//

#ifndef __jass__buffer_object__
#define __jass__buffer_object__

#include "jass/jass.h"

class BufferObject : private boost::noncopyable {
public:
  BufferObject(const GLenum target);
  ~BufferObject(void);

  void Create(void);

  bool Bind(std::function<void(GLenum)> const &func);
private:
  GLenum target_;
  GLuint vbo_id_;
};

#endif /* defined(__jass__buffer_object__) */
