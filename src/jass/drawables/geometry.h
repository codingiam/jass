// Copyright (c) 2016, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_DRAWABLES_GEOMETRY_H_
#define JASS_DRAWABLES_GEOMETRY_H_

#include <boost/filesystem.hpp>

#include <string>
#include <vector>
#include <memory>

#include <tiny_obj_loader.h>

#include "jass/drawables/drawable.h"


namespace GL {
class VertexArrayObject;
class VertexBufferObject;
class Texture;
class Program;
}

namespace Drawables {

class Geometry : public Drawable {
 public:
  explicit Geometry(boost::filesystem::path const &path);
  virtual ~Geometry(void);

  void Create(void) override;
  void Render(void) override;

 private:
  std::shared_ptr<GL::Program> program_;

  std::vector<tinyobj::shape_t> shapes_;
  std::vector<tinyobj::material_t> materials_;

  boost::filesystem::path path_;

  std::shared_ptr<GL::Texture> texture_;

  std::shared_ptr<GL::VertexArrayObject> vao_;
  std::shared_ptr<GL::VertexBufferObject> tvbo_;
  std::shared_ptr<GL::VertexBufferObject> nvbo_;
  std::shared_ptr<GL::VertexBufferObject> pvbo_;
  std::shared_ptr<GL::VertexBufferObject> ivbo_;
};

}  // namespace Drawables

#endif  // JASS_DRAWABLES_GEOMETRY_H_
