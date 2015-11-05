// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/font_drawable.h"

#include "jass/image.h"
#include "jass/texture.h"

#include "jass/video.h"
#include "jass/window.h"

#include "jass/vertex_shader.h"
#include "jass/fragment_shader.h"
#include "jass/program.h"
#include "jass/vertex_array_object.h"
#include "jass/buffer_object.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Drawables {

  FontDrawable::FontDrawable(std::string const &path) : path_(path) {
  }

  FontDrawable::~FontDrawable() {
    texture_.reset();
    program_.reset();
  }

  void FontDrawable::Create(void) {
    std::shared_ptr<Image> image = Image::MakeImage(path_);
    this->texture_ = Texture::MakeTexture(image);

    auto vertex_shader = std::make_shared<VertexShader>();
    vertex_shader->Create();

    auto fragment_shader = std::make_shared<FragmentShader>();
    fragment_shader->Create();

    this->program_ = std::make_shared<Program>();
    program_->Create(vertex_shader, fragment_shader);
  }

  void FontDrawable::Render(Video *const video) {
    auto model = glm::scale(glm::translate(glm::mat4(), position()), this->scale());
    auto view = glm::mat4();
    auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);

    auto mvp = projection * view * model;

    VertexArrayObject vao;

    vao.Create();

    auto program = program_;
    auto texture = texture_;
    auto text = text_;

    std::function<void(void)> func = [program, mvp, texture, text] () {

      glUseProgram(program->program_id_);

      texture->Bind();

      BufferObject vbo;

      vbo.Create();

      std::function<void(void)> func = [text] () {
        const char *p = nullptr;

        float x2 = 0, y2 = 0, w = 160, h = 160;

        for(p = text.c_str(); *p; p++) {
          GLfloat box[4][5] = {
            {x2,      y2    , 0.0f,  0, 0},
            {x2 + w,  y2    , 0.0f,  1, 0},
            {x2,      y2 + h, 0.0f,  0, 1},
            {x2 + w,  y2 + h, 0.0f,  1, 1},
          };

          GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW));

          x2 += 16;
        }
      };

      vbo.Bind(func);

      func = [program, mvp] () {
        GLint loc_vert, loc_tex;

        GL_CHECK(loc_vert = glGetAttribLocation(program->program_id_, "vp_modelspace"));

        GL_CHECK(glVertexAttribPointer(
                                       loc_vert,
                                       3,                  // size
                                       GL_FLOAT,           // type
                                       GL_FALSE,           // normalized?
                                       5 * sizeof(float),  // stride
                                       0                   // array buffer offset
                                       ));

        GL_CHECK(loc_tex = glGetAttribLocation(program->program_id_, "texcoord"));

        GL_CHECK(glVertexAttribPointer(
                                       loc_tex,
                                       2,                  // size
                                       GL_FLOAT,           // type
                                       GL_FALSE,           // normalized?
                                       5 * sizeof(float),  // stride
                                       (void *)(3 * sizeof(float))  // array buffer offset
                                       ));
        // xxxx

        GL_CHECK(glUseProgram(program->program_id_));

        GL_CHECK(glEnableVertexAttribArray(loc_vert));
        GL_CHECK(glEnableVertexAttribArray(loc_tex));

        GLint loc_trans = glGetUniformLocation(program->program_id_, "trans");
        glUniformMatrix4fv(loc_trans, 1, GL_FALSE, glm::value_ptr(mvp));

        GLint loc_color = glGetUniformLocation(program->program_id_, "theColor");
        float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glUniform4fv(loc_color, 1, color);

        GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
        
        GL_CHECK(glEnableVertexAttribArray(loc_tex));
        GL_CHECK(glDisableVertexAttribArray(loc_vert));
      };
      
      vbo.Bind(func);
      
      glUseProgram(0);
    };
    
    vao.Bind(func);
  }
}
