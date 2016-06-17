// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/play_board_game_object.h"

#include "jass/drawables/bitmap_drawable.h"

namespace GameObjects {

  PlayBoardGameObject::PlayBoardGameObject() {
  }

  PlayBoardGameObject::~PlayBoardGameObject() {
    bg_board_.reset();
  }

  void PlayBoardGameObject::Create() {
    this->bg_board_ = std::make_shared<Drawables::BitampDrawable>("data/texturi/board.png");
    this->bg_board_->Create();
  }

  void PlayBoardGameObject::Render(Video *const video) {
    bg_board_->position(glm::vec3(10, 530, 0));
    bg_board_->scale(glm::vec3(780.0 / bg_board_->width(), 64.0 / bg_board_->height(), 1.0));
    bg_board_->Render(video);
  }

}  // namespace GameObjects
