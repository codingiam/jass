// Copyright (c) 2015, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/bitmap.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "jass/resources/image.h"
#include "jass/gl/texture.h"

#include "jass/shaders/vertex_shader.h"
#include "jass/shaders/fragment_shader.h"
#include "jass/shaders/program.h"
#include "jass/gl/vertex_array_object.h"
#include "jass/gl/vertex_buffer_object.h"

namespace Drawables {

Bitmap::Bitmap(std::string const &path) : path_(path) {
  this->width_ = 0;
  this->height_ = 0;
}

Bitmap::~Bitmap() {
  texture_.reset();
  program_.reset();
}

void Bitmap::Create(void) {
  std::shared_ptr<Resources::Image> image = Resources::Image::MakeImage(path_);
  this->texture_ = GL::Texture::MakeTexture(image);
  this->width_ = image->width();
  this->height_ = image->height();

  auto vertex_shader =
      std::make_shared<Shaders::VertexShader>(
          "resources/shaders/2default.vert");
  vertex_shader->Create();

  auto fragment_shader =
      std::make_shared<Shaders::FragmentShader>(
          "resources/shaders/2default.frag");
  fragment_shader->Create();

  this->program_ = std::make_shared<Shaders::Program>();
  program_->Create(vertex_shader, fragment_shader);

  this->vao_ = std::make_shared<GL::VertexArrayObject>();
  vao_->Create();

  this->vbo_ = std::make_shared<GL::VertexBufferObject>(GL_ARRAY_BUFFER);
  vbo_->Create();
}

void Bitmap::Render() {
  auto model = glm::translate(translation()) * glm::mat4_cast(rotation()) *
      glm::scale(scale());
  auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);

  auto mp = projection * model;

  auto program = program_;
  auto texture = texture_;
  auto color = this->color();
  auto vbo = this->vbo_;

  const GLfloat g_vertex_buffer_data[] = {
    // Left bottom triangle
      0.0f, height_, 0.0f, 1.0f,
      0.0f,    0.0f, 0.0f, 0.0f,
    width_,    0.0f, 1.0f, 0.0f,
    // Right top triangle
    width_,    0.0f, 1.0f, 0.0f,
    width_, height_, 1.0f, 1.0f,
      0.0f, height_, 0.0f, 1.0f
  };

  std::function<void(void)> func = [vbo, program, model, mp, texture,
      g_vertex_buffer_data, color] () {
    glUseProgram(program->program_id_);

    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    glUniform1i(glGetUniformLocation(program->program_id_, "tex"), 0);

    std::function<void(GLenum)> func =
        [g_vertex_buffer_data] (GLenum target) {
          glBufferData(target, sizeof(g_vertex_buffer_data),
              g_vertex_buffer_data, GL_STATIC_DRAW);
    };

    vbo->Bind(func);

    func = [program, model, mp, color] (GLenum target) {
      GLint loc_vert, loc_tex;

      loc_vert = glGetAttribLocation(program->program_id_,
          "position");

      glVertexAttribPointer(
              loc_vert,
              2,                  // size
              GL_FLOAT,           // type
              GL_FALSE,           // normalized?
              4 * sizeof(float),  // stride
              0                   // array buffer offset
      );

      loc_tex = glGetAttribLocation(program->program_id_, "vUV");

      glVertexAttribPointer(
               loc_tex,
               2,                  // size
               GL_FLOAT,           // type
               GL_FALSE,           // normalized?
               4 * sizeof(float),  // stride
               (void *)(2 * sizeof(float))  // array buffer offset
      );

      // GL_CHECK(glUseProgram(program->program_id_));

      glEnableVertexAttribArray(loc_vert);
      glEnableVertexAttribArray(loc_tex);

      GLint loc_mvp = glGetUniformLocation(program->program_id_, "mp");
      glUniformMatrix4fv(loc_mvp, 1, GL_FALSE, glm::value_ptr(mp));

      GLint loc_color = glGetUniformLocation(program->program_id_,
          "objectColor");
      glUniform4fv(loc_color, 1, glm::value_ptr(color));

      glDrawArrays(GL_TRIANGLES, 0, 6);

      glDisableVertexAttribArray(loc_tex);
      glDisableVertexAttribArray(loc_vert);
    };

    vbo->Bind(func);

    glUseProgram(0);
  };

  vao_->Bind(func);
}

}  // namespace Drawables
