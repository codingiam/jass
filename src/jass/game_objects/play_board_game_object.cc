// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/game_objects/play_board_game_object.h"

#include "jass/window.h"

#include "jass/video.h"
#include "jass/image.h"
#include "jass/texture.h"

namespace GameObjects {

  PlayBoardGameObject::PlayBoardGameObject() {
  }

  PlayBoardGameObject::~PlayBoardGameObject() {
    bg_board_.reset();
  }

  void PlayBoardGameObject::Create() {
    std::shared_ptr<Image> image = Image::MakeImage("data/texturi/board.png");
    this->bg_board_ = Texture::MakeTexture(image);
  }

  void PlayBoardGameObject::Render(Video *const video) {
    GL_CHECK(glColor4f(1.0f, 1.0f, 1.0f, 1.0f));
    video->DrawTexture(10, 530, 780, 64, bg_board_);
  }

}
