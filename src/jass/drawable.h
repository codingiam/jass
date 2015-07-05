#pragma once

#include "jass/jass.h"

class Video;

namespace Drawables {

  class Drawable : private boost::noncopyable {
  public:
    Drawable(void);
    virtual ~Drawable(void);

    virtual void Create(void) = 0;
    virtual void Render(Video *const video) = 0;
  };

}
