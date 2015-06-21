#include "image.h"

Image::Image(void) {
  this->texid_ = 0;
}

Image::~Image(void) {
  if (texid_) {
    ilDeleteImages(1, &texid_);
    this->texid_ = 0;
  }
}

bool Image::loadImage(std::string const &file_name) {
  if (texid_) {
    return false;
  }

  ilGenImages(1, &this->texid_); 
  
  ilBindImage(texid_);

  bool loaded = ilLoadImage(file_name.c_str()) == IL_TRUE;
  if (loaded) {
    loaded = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) == IL_TRUE;
  }

  ilBindImage(0);

  return loaded;
}
