#pragma once

#include "jass/jass.h"

#include <glm/vec3.hpp>

class Video;

namespace Drawables {

  class Drawable : private boost::noncopyable {
  public:
    Drawable(void);
    virtual ~Drawable(void);

    virtual void Create(void) = 0;
    virtual void Render(Video *const video) = 0;

    void position(const glm::vec3 &position) {
      this->position_ = position;
    }

    glm::vec3 position(void) {
      return position_;
    }

  private:
    glm::vec3 position_;
  };

}
