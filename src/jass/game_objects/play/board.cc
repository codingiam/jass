// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/play/board.h"

#include "jass/drawables/bitmap.h"

namespace GameObjects {
namespace Play {

Board::Board() {
}

Board::~Board() {
  bg_board_.reset();
}

void Board::Create() {
  this->bg_board_ =
      std::make_shared<Drawables::Bitmap>("resources/textures/board.png");
  this->bg_board_->Create();
}

void Board::Render(Video *const video) {
  bg_board_->translation(glm::vec3(10, 530, 0));
  bg_board_->scale(glm::vec3(780.0 / bg_board_->width(),
      64.0 / bg_board_->height(), 1.0));
  bg_board_->color(glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
  bg_board_->Render(video);
}

}  // namespace Play
}  // namespace GameObjects
