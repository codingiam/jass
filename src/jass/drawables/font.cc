// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/font.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <array>

#include "jass/resources/image.h"
#include "jass/gl/texture.h"

#include "jass/gl/vertex_shader.h"
#include "jass/gl/fragment_shader.h"
#include "jass/gl/program.h"
#include "jass/gl/vertex_array_object.h"
#include "jass/gl/vertex_buffer_object.h"

namespace Drawables {

Font::Font(boost::filesystem::path const &path) : path_(path) {
}

Font::~Font() {
  texture_.reset();
  program_.reset();
}

void Font::Create(void) {
  std::shared_ptr<Resources::Image> image = Resources::Image::MakeImage(path_);
  this->texture_ = GL::Texture::MakeTexture(image);

  this->program_ = std::make_shared<GL::Program>();
  program_->Create("resources/shaders/2default.vert",
      "resources/shaders/2default.frag");

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
    glUseProgram(program->program_id());

    texture->Bind();

    std::function<void(GLenum)> func = [text] (GLenum target) {
      GLfloat x2 = 0, y2 = 0;

      std::vector<std::array<std::array<GLfloat, 4>, 6> > vertices;

      for (const char *p = text.c_str(); *p; p++) {
        int tx, ty;

        tx = ((*p - 32) % 16) * 16;
        ty = ((*p - 32) / 16) * 16;

        vertices.push_back({{
            { x2,       y2,      tx / 256.0f,        ty / 256.0f },
            { x2 + 15,  y2,      (tx + 15) / 256.0f, ty / 256.0f },
            { x2,       y2 + 15, tx / 256.0f,        (ty + 15) / 256.0f },
            { x2,       y2 + 15, tx / 256.0f,        (ty + 15) / 256.0f },
            { x2 + 15,  y2,      (tx + 15) / 256.0f, ty / 256.0f },
            { x2 + 15,  y2 + 15, (tx + 15) / 256.0f, (ty + 15) / 256.0f },
        }});

        x2 += 16;
      }

      glBufferData(target, vertices.size() *
          sizeof(decltype(vertices)::value_type),
          &vertices[0], GL_DYNAMIC_DRAW);
    };

    vbo->Bind(func);

    func = [program, model, mp, text, color] (GLenum target) {
      GLint loc_vert = glGetAttribLocation(program->program_id(), "vPosition");

      glVertexAttribPointer(
          loc_vert,
          2,
          GL_FLOAT,
          GL_FALSE,
          4 * sizeof(GLfloat),
          0);

      glEnableVertexAttribArray(loc_vert);

      GLint loc_tex = glGetAttribLocation(program->program_id(), "vUV");

      glVertexAttribPointer(
          loc_tex,
          2,
          GL_FLOAT,
          GL_FALSE,
          4 * sizeof(GLfloat),
          reinterpret_cast<GLvoid *>(2 * sizeof(GLfloat)));

      glEnableVertexAttribArray(loc_tex);

      GLint loc_mvp = glGetUniformLocation(program->program_id(), "mp");
      glUniformMatrix4fv(loc_mvp, 1, GL_FALSE, glm::value_ptr(mp));

      GLint loc_color = glGetUniformLocation(program->program_id(),
          "objectColor");
      glUniform4fv(loc_color, 1, glm::value_ptr(color));

      glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(6 * text.length()));

      glDisableVertexAttribArray(loc_tex);
      glDisableVertexAttribArray(loc_vert);
    };

    vbo->Bind(func);

    glUseProgram(0);
  };

  vao_->Bind(vao_func);
}

}  // namespace Drawables
