// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/bitmap_drawable.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "jass/image.h"
#include "jass/texture.h"

#include "jass/video.h"
#include "jass/window.h"

#include "jass/shaders/vertex_shader.h"
#include "jass/shaders/fragment_shader.h"
#include "jass/shaders/program.h"
#include "jass/vertex_array_object.h"
#include "jass/buffer_object.h"

namespace Drawables {

  BitampDrawable::BitampDrawable(std::string const &path) : path_(path) {
    this->width_ = 0;
    this->height_ = 0;
  }

  BitampDrawable::~BitampDrawable() {
    texture_.reset();
    program_.reset();
  }

  void BitampDrawable::Create(void) {
    std::shared_ptr<Image> image = Image::MakeImage(path_);
    this->texture_ = Texture::MakeTexture(image);
    this->width_ = image->width();
    this->height_ = image->height();

    auto vertex_shader = std::make_shared<Shaders::VertexShader>();
    vertex_shader->Create();

    auto fragment_shader = std::make_shared<Shaders::FragmentShader>();
    fragment_shader->Create();

    this->program_ = std::make_shared<Shaders::Program>();
    program_->Create(vertex_shader, fragment_shader);
  }

  void BitampDrawable::Render(Video *const video) {
    auto model = glm::translate(translation()) * glm::mat4_cast(rotation()) * glm::scale(scale());
    auto view = glm::mat4();
    auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);

    auto mvp = projection * view * model;

    VertexArrayObject vao;

    vao.Create();

    auto program = program_;
    auto texture = texture_;
    auto color = this->color();

    const GLfloat g_vertex_buffer_data[] = {
      // Left bottom triangle
        0.0f, height_, 0.0f, 0.0f, 1.0f,
        0.0f,    0.0f, 0.0f, 0.0f, 0.0f,
      width_,    0.0f, 0.0f, 1.0f, 0.0f,
      // Right top triangle
      width_,    0.0f, 0.0f, 1.0f, 0.0f,
      width_, height_, 0.0f, 1.0f, 1.0f,
        0.0f, height_, 0.0f, 0.0f, 1.0f
    };

    std::function<void(void)> func = [program, mvp, texture, g_vertex_buffer_data, color] () {
      glUseProgram(program->program_id_);

      texture->Bind();
      // glUniform1i(glGetUniformLocation(program->program_id_, "tex"), 0);

      BufferObject vbo(GL_ARRAY_BUFFER);

      vbo.Create();

      std::function<void(GLenum)> func = [g_vertex_buffer_data] (GLenum target) {
        GL_CHECK(glBufferData(target, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));
      };

      vbo.Bind(func);

      func = [program, mvp, color] (GLenum target) {
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
        glUniform4fv(loc_color, 1, glm::value_ptr(color));

        GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));

        GL_CHECK(glDisableVertexAttribArray(loc_tex));
        GL_CHECK(glDisableVertexAttribArray(loc_vert));
      };

      vbo.Bind(func);

      glUseProgram(0);
    };

    vao.Bind(func);
  }
}  // namespace Drawables
