// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "jass/jass.h"

namespace GameObjects {
  class GameObject : private boost::noncopyable {
   public:
    GameObject(void);
    virtual ~GameObject(void);

    virtual void Create(void) = 0;
    virtual void Start(void) = 0;

    virtual bool Updatable(void);
    virtual bool Renderable(void);
  };
}
