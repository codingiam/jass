// Copyright (c) 2016, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/geometry_drawable.h"

#include "jass/video.h"
#include "jass/program.h"

namespace Drawables {

  GeometryDrawable::GeometryDrawable(std::string const &path) : path_(path) {
  }

  GeometryDrawable::~GeometryDrawable() {
    program_.reset();
  }

  void GeometryDrawable::Create() {
    std::string err;

    bool ret = tinyobj::LoadObj(shapes_, materials_, err, path_.c_str());

    if (!ret) {
      boost::format message =
        boost::format("Geometry not loaded %s, error %s") % path_ % err;
      throw std::runtime_error(message.str());
    }
  }

  void GeometryDrawable::Render(Video *const video) {
  }

}  // namespace Drawables
