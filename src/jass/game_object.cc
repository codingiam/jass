// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_object.h"

namespace GameObjects {
  GameObject::GameObject() {
  }

  GameObject::GameObject(std::shared_ptr<GameObject> const &parent) : parent_(parent) {
  }

  GameObject::~GameObject() {
  }
}