// Copyright (c) 2016, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/geometry_drawable.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "jass/video.h"

#include "jass/shaders/vertex_shader.h"
#include "jass/shaders/fragment_shader.h"
#include "jass/shaders/program.h"

#include "jass/vertex_array_object.h"
#include "jass/buffer_object.h"

namespace Drawables {

  GeometryDrawable::GeometryDrawable(std::string const &path) : path_(path) {
  }

  GeometryDrawable::~GeometryDrawable() {
    program_.reset();
  }

  void GeometryDrawable::Create() {
    std::string err;

    bool ret = tinyobj::LoadObj(shapes_, materials_, err, path_.c_str());

    if (!ret) {
      boost::format message =
        boost::format("Geometry not loaded %s, error %s") % path_ % err;
      throw std::runtime_error(message.str());
    }

    auto vertex_shader = std::make_shared<Shaders::VertexShader>();
    vertex_shader->Create();

    auto fragment_shader = std::make_shared<Shaders::FragmentShader>();
    fragment_shader->Create();

    this->program_ = std::make_shared<Shaders::Program>();
    program_->Create(vertex_shader, fragment_shader);
  }

  void GeometryDrawable::Render(Video *const video) {
    auto model = glm::translate(translation()) * glm::mat4_cast(rotation()) * glm::scale(scale());
    auto view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    auto projection = glm::perspective(glm::radians(45.0f), (GLfloat) 800 / (GLfloat) 600, 0.1f, 100.0f);

    auto mvp = projection * view * model;

    VertexArrayObject vao;

    vao.Create();

    auto program = program_;
  //   auto texture = texture_;
    auto color = this->color();

    auto positions = this->shapes_[0].mesh.positions;
    auto indices = this->shapes_[0].mesh.indices;

  //   const GLfloat g_vertex_buffer_data[] = {
  //     // Left bottom triangle
  //       0.0f, height_, 0.0f, 0.0f, 1.0f,
  //       0.0f,    0.0f, 0.0f, 0.0f, 0.0f,
  //     width_,    0.0f, 0.0f, 1.0f, 0.0f,
  //     // Right top triangle
  //     width_,    0.0f, 0.0f, 1.0f, 0.0f,
  //     width_, height_, 0.0f, 1.0f, 1.0f,
  //       0.0f, height_, 0.0f, 0.0f, 1.0f
  //   };

    std::function<void(void)> vao_func = [program, mvp, /*texture, g_vertex_buffer_data,*/positions, indices, color] () {
      glUseProgram(program->program_id_);

  //     texture->Bind();
  //     // glUniform1i(glGetUniformLocation(program->program_id_, "tex"), 0);

      BufferObject pvbo(GL_ARRAY_BUFFER);

      pvbo.Create();

      std::function<void(GLenum)> pvbo_func = [positions] (GLenum target) {
        GL_CHECK(glBufferData(target, positions.size() * sizeof(decltype(positions)::value_type), positions.data(), GL_STATIC_DRAW));
      };

      pvbo.Bind(pvbo_func);

      pvbo_func = [program, mvp, color] (GLenum target) {
        GLint loc_vert/*, loc_tex*/;

	      GL_CHECK(loc_vert = glGetAttribLocation(program->program_id_, "vp_modelspace"));

        GL_CHECK(glVertexAttribPointer(
                loc_vert,
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                3 * sizeof(float),  // stride
                0                   // array buffer offset
        ));

  //       GL_CHECK(loc_tex = glGetAttribLocation(program->program_id_, "texcoord"));

  //       GL_CHECK(glVertexAttribPointer(
  //                loc_tex,
  //                2,                  // size
  //                GL_FLOAT,           // type
  //                GL_FALSE,           // normalized?
  //                5 * sizeof(float),  // stride
  //                (void *)(3 * sizeof(float))  // array buffer offset
  //       ));
  //       // xxxx

        GL_CHECK(glUseProgram(program->program_id_));

        GL_CHECK(glEnableVertexAttribArray(loc_vert));
  //       GL_CHECK(glEnableVertexAttribArray(loc_tex));

        GLint loc_trans = glGetUniformLocation(program->program_id_, "trans");
        glUniformMatrix4fv(loc_trans, 1, GL_FALSE, glm::value_ptr(mvp));

        GLint loc_color = glGetUniformLocation(program->program_id_, "theColor");
        glUniform4fv(loc_color, 1, glm::value_ptr(color));

  //       GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));

  //       GL_CHECK(glDisableVertexAttribArray(loc_tex));
  //       GL_CHECK(glDisableVertexAttribArray(loc_vert));
      };

      pvbo.Bind(pvbo_func);

      BufferObject ivbo(GL_ELEMENT_ARRAY_BUFFER);

      ivbo.Create();

      std::function<void(GLenum)> ivbo_func = [indices] (GLenum target) {
        GL_CHECK(glBufferData(target, indices.size() * sizeof(decltype(indices)::value_type), indices.data(), GL_STATIC_DRAW));

        glDrawElements(
          GL_TRIANGLES,      // mode
          indices.size(),    // count
          GL_UNSIGNED_INT,   // type
          (void*)0           // element array buffer offset
        );
      };

      ivbo.Bind(ivbo_func);

      glUseProgram(0);
    };

    vao.Bind(vao_func);
  }

}  // namespace Drawables
