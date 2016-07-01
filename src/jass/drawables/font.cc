// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/font.h"

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

Font::Font(std::string const &path) : path_(path) {
}

Font::~Font() {
  texture_.reset();
  program_.reset();
}

void Font::Create(void) {
  std::shared_ptr<Resources::Image> image = Resources::Image::MakeImage(path_);
  this->texture_ = GL::Texture::MakeTexture(image);

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

void Font::Render() {
  auto model = glm::translate(translation()) * glm::mat4_cast(rotation()) *
      glm::scale(scale());
  auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);

  auto mp = projection * model;

  auto program = program_;
  auto texture = texture_;
  auto text = text_;
  auto color = this->color();
  auto vbo = this->vbo_;

  std::function<void(void)> vao_func = [vbo, program, model, mp, texture, text,
      color] () {
    glUseProgram(program->program_id_);

    texture->Bind();

    std::function<void(GLenum)> func = [text] (GLenum target) {
      const char *p = nullptr;

      float x2 = 0, y2 = 0;

      typedef std::array<std::array<GLfloat, 5>, 6> tBox;

      std::vector<tBox> vertices;

      for(p = text.c_str(); *p; p++) {
        int tx, ty;

        tx = ((*p - 32) % 16) * 16;
        ty = ((*p - 32) / 16) * 16;

        tBox box = {{
          { x2,       y2,      0.0f, tx / 256.0f,        ty / 256.0f },
          { x2 + 15,  y2,      0.0f, (tx + 15) / 256.0f, ty / 256.0f },
          { x2,       y2 + 15, 0.0f, tx / 256.0f,        (ty + 15) / 256.0f },
          { x2,       y2 + 15, 0.0f, tx / 256.0f,        (ty + 15) / 256.0f },
          { x2 + 15,  y2,      0.0f, (tx + 15) / 256.0f, ty / 256.0f },
          { x2 + 15,  y2 + 15, 0.0f, (tx + 15) / 256.0f, (ty + 15) / 256.0f },
        }};

        vertices.push_back(box);

        x2 += 16;
      }

      glBufferData(target, vertices.size() * sizeof (tBox),
          &vertices[0], GL_DYNAMIC_DRAW);
    };

    vbo->Bind(func);

    func = [program, model, mp, text, color] (GLenum target) {
      GLint loc_vert, loc_tex;

      loc_vert = glGetAttribLocation(program->program_id_,
          "position");

      glVertexAttribPointer(
                                     loc_vert,
                                     2,                  // size
                                     GL_FLOAT,           // type
                                     GL_FALSE,           // normalized?
                                     5 * sizeof(float),  // stride
                                     0);

      loc_tex = glGetAttribLocation(program->program_id_, "vUV");

      glVertexAttribPointer(
                                     loc_tex,
                                     2,                  // size
                                     GL_FLOAT,           // type
                                     GL_FALSE,           // normalized?
                                     5 * sizeof(float),  // stride
                                     (void *)(3 * sizeof(float)));

      // GL_CHECK(glUseProgram(program->program_id_));

      glEnableVertexAttribArray(loc_vert);
      glEnableVertexAttribArray(loc_tex);

      GLint loc_mvp = glGetUniformLocation(program->program_id_, "mp");
      glUniformMatrix4fv(loc_mvp, 1, GL_FALSE, glm::value_ptr(mp));

      GLint loc_color = glGetUniformLocation(program->program_id_,
          "objectColor");
      glUniform4fv(loc_color, 1, glm::value_ptr(color));

      glDrawArrays(GL_TRIANGLES, 0, 6 * text.length());

      glDisableVertexAttribArray(loc_tex);
      glDisableVertexAttribArray(loc_vert);
    };

    vbo->Bind(func);

    glUseProgram(0);
  };

  vao_->Bind(vao_func);
}

}  // namespace Drawables
