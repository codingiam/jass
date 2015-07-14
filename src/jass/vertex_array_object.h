//
//  vertex_array_object.h
//  jass
//
//  Created by Doru Budai on 13/07/15.
//  Copyright (c) 2015 Doru Budai. All rights reserved.
//

#ifndef __jass__vertex_array_object__
#define __jass__vertex_array_object__

#include "jass/jass.h"

class VertexArrayObject : private boost::noncopyable {
public:
  VertexArrayObject(void);
  ~VertexArrayObject(void);

  void Create(void);

  bool Bind(std::function<void()> const &func);
private:
  GLuint vao_id_;
};

#endif /* defined(__jass__vertex_array_object__) */
