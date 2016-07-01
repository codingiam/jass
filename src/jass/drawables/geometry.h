// Copyright (c) 2016, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "jass/drawables/drawable.h"
#include "jass/resources/tiny_obj_loader.h"

namespace GL {
class VertexArrayObject;
class VertexBufferObject;
class Texture;
}

namespace Shaders {
class Program;
}

namespace Drawables {

class Geometry : public Drawable {
 public:
  explicit Geometry(std::string const &path);
  virtual ~Geometry(void);

  void Create(void) override;
  void Render(void) override;

 private:
  std::shared_ptr<Shaders::Program> program_;

  std::vector<tinyobj::shape_t> shapes_;
  std::vector<tinyobj::material_t> materials_;

  std::string path_;

  std::shared_ptr<GL::Texture> texture_;

  std::shared_ptr<GL::VertexArrayObject> vao_;
  std::shared_ptr<GL::VertexBufferObject> tvbo_;
  std::shared_ptr<GL::VertexBufferObject> nvbo_;
  std::shared_ptr<GL::VertexBufferObject> pvbo_;
  std::shared_ptr<GL::VertexBufferObject> ivbo_;
};

}  // namespace Drawables
