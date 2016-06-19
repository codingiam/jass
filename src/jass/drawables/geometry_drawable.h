// Copyright (c) 2016, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <glm/vec4.hpp>

#include <string>
#include <vector>

#include "jass/drawables/drawable.h"
#include "jass/tiny_obj_loader.h"

class Video;

namespace Shaders {
  class Program;
}

namespace Drawables {

class GeometryDrawable : public Drawable {
 public:
  GeometryDrawable(std::string const &path);
  virtual ~GeometryDrawable(void);

  void Create(void) override;
  void Render(Video *const video) override;

 private:
  std::shared_ptr<Shaders::Program> program_;

  std::vector<tinyobj::shape_t> shapes_;
  std::vector<tinyobj::material_t> materials_;

  std::string path_;
};

}  // namespace Drawables
