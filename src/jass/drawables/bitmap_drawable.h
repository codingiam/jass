#pragma once

#include "jass/drawables/drawable.h"

#include <glm/vec4.hpp>

class Video;
class Texture;
class Program;

namespace Drawables {

  class BitampDrawable : public Drawable {
   public:
    BitampDrawable(std::string const &path);
    virtual ~BitampDrawable(void);

    void Create(void) override;
    void Render(Video *const video) override;

    GLfloat width(void) { return width_; }
    GLfloat height(void) { return height_; }

    void color(const glm::vec4 &color) {
      this->color_ = color;
    }

   private:
    std::shared_ptr<Program> program_;

    std::shared_ptr<Texture> texture_;
     
    std::string path_;

    GLfloat width_;
    GLfloat height_;

    glm::vec4 color_;
  };

}
