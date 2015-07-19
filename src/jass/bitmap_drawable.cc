#include "jass/bitmap_drawable.h"

#include "jass/image.h"
#include "jass/texture.h"

#include "jass/video.h"
#include "jass/window.h"

namespace Drawables {

  BitampDrawable::BitampDrawable(std::string const &path) : path_(path) {
  }

  BitampDrawable::~BitampDrawable() {
    texture_.reset();
  }

  void BitampDrawable::Create(void) {
    std::shared_ptr<Image> image = Image::MakeImage(path_);
    this->texture_ = Texture::MakeTexture(image);
  }

  void BitampDrawable::Render(Video *const video, const GLint x, const GLint y) {
    GL_CHECK(glColor4f(1.0f, 1.0f, 1.0f, 1.0f));
    video->DrawTexture(x, y, Window::kWidth, Window::kHeight, texture_);
  }
}
