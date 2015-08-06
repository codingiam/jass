#pragma once

#include "jass/drawable.h"

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

   private:
     std::shared_ptr<Program> program_;

     std::shared_ptr<Texture> texture_;
     
     std::string path_;
  };

}
