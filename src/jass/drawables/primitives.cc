// Copyright (c) 2016, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/primitives.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "jass/gl/vertex_shader.h"
#include "jass/gl/fragment_shader.h"
#include "jass/gl/program.h"
#include "jass/gl/vertex_array_object.h"
#include "jass/gl/vertex_buffer_object.h"

namespace Drawables {

Primitives::Primitives() {
}

Primitives::~Primitives() {
}

void Primitives::Create() {
  this->program_ = std::make_shared<GL::Program>();
  program_->Create("resources/shaders/3duntextured.vert",
      "resources/shaders/3duntextured.frag");

  this->vao_ = std::make_shared<GL::VertexArrayObject>();
  vao_->Create();

  this->vbo_ = std::make_shared<GL::VertexBufferObject>(GL_ARRAY_BUFFER);
  vbo_->Create();
}

void Primitives::Render() {
  auto model = glm::translate(translation()) * glm::mat4_cast(rotation()) *
      glm::scale(scale());
  auto view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  auto projection =
      glm::perspective(glm::radians(45.0f), (GLfloat) 800 / (GLfloat) 600,
          0.1f, 100.0f);

  auto mvp = projection * view * model;

  auto program = this->program_;

  auto positions = this->vertices_;
  auto vbo = this->vbo_;
  auto point_size = this->point_size_;
  auto colors = this->colors_;

  std::function<void(void)> vao_func = [vbo, program, model, mvp, positions,
      colors, point_size] () {
    glUseProgram(program->program_id());

    std::function<void(GLenum)> vbo_func = [program, model, mvp, positions,
        colors, point_size] (GLenum target) {
      glBufferData(target,
          positions.size() * sizeof(decltype(positions)::value_type),
          positions.data(), GL_DYNAMIC_DRAW);

      GLint loc_vert = glGetAttribLocation(program->program_id(), "vPosition");

      glVertexAttribPointer(
          static_cast<GLuint>(loc_vert),
          2,
          GL_FLOAT,
          GL_FALSE,
          2 * sizeof(float),
          0);
      glEnableVertexAttribArray(static_cast<GLuint>(loc_vert));

      GLint loc_mvp = glGetUniformLocation(program->program_id(), "mvp");
      glUniformMatrix4fv(loc_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

      glPointSize(point_size);

      glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(positions.size()));
    };

    vbo->Bind(vbo_func);

    glUseProgram(0);
  };

  vao_->Bind(vao_func);
}

}  // namespace Drawables
