#pragma once

#include "jass/drawable.h"

class Video;
class Texture;

namespace Drawables {

  class BitampDrawable : public Drawable {
   public:
    BitampDrawable(std::string const &path);
    virtual ~BitampDrawable(void);

    virtual void Create(void) override;
    void Render(Video *const video) override { }

    void Render(Video *const video, const GLint x, const GLint y);

   private:
     std::shared_ptr<Texture> texture_;
     
     std::string path_;
  };

}
