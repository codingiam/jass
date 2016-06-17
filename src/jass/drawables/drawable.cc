#include "jass/drawables/drawable.h"

namespace Drawables {

  Drawable::Drawable() {
    this->scale_ = glm::vec3(1.0);
  }

  Drawable::~Drawable() {
  }

}
