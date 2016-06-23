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

    auto vertex_shader = std::make_shared<Shaders::VertexShader>("data/shaders/3default.vert");
    vertex_shader->Create();

    auto fragment_shader = std::make_shared<Shaders::FragmentShader>("data/shaders/3default.frag");
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

    auto program = this->program_;
  //  auto texture = texture_;
  //  auto color = this->color();

    auto positions = this->shapes_[0].mesh.positions;
    auto normals = this->shapes_[0].mesh.normals;
    auto texcoords = this->shapes_[0].mesh.texcoords;
    auto indices = this->shapes_[0].mesh.indices;
    auto material = this->materials_[0];

    // std::cout << positions.size() << std::endl;
    // std::cout << normals.size() << std::endl;
    // std::cout << texcoords.size() << std::endl;
    // std::cout << indices.size() << std::endl;
    // std::cout << "***" << std::endl;

    std::function<void(void)> vao_func = [program, model, mvp, /*texture*/positions, normals, indices, /*color*/material] () {
      GL_CHECK(glUseProgram(program->program_id_));

      // std::cout << "a0=" << glGetAttribLocation(program->program_id_, "vpModelspace") << std::endl;
      // std::cout << "a1=" << glGetAttribLocation(program->program_id_, "vUV") << std::endl;
      // std::cout << "a2=" << glGetAttribLocation(program->program_id_, "van_modelspace") << std::endl;

  //     texture->Bind();
  //     // glUniform1i(glGetUniformLocation(program->program_id_, "tex"), 0);

      BufferObject nvbo(GL_ARRAY_BUFFER);

      nvbo.Create();

      std::function<void(GLenum)> nvbo_func = [program, normals] (GLenum target) {
        GL_CHECK(glBufferData(target, normals.size() * sizeof(decltype(normals)::value_type), normals.data(), GL_STATIC_DRAW));

        GLint loc_vn;

	      GL_CHECK(loc_vn = glGetAttribLocation(program->program_id_, "vnModelspace"));

        loc_vn = 2;

        GL_CHECK(glVertexAttribPointer(
                loc_vn,
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                3 * sizeof(float),  // stride
                0                   // array buffer offset
        ));

        GL_CHECK(glEnableVertexAttribArray(loc_vn));
      };

      nvbo.Bind(nvbo_func);

      BufferObject pvbo(GL_ARRAY_BUFFER);

      pvbo.Create();

      std::function<void(GLenum)> pvbo_func = [program, model, mvp, positions, /*color*/material] (GLenum target) {
        GL_CHECK(glBufferData(target, positions.size() * sizeof(decltype(positions)::value_type), positions.data(), GL_STATIC_DRAW));

        GLint loc_vert/*, loc_tex*/;

	      GL_CHECK(loc_vert = glGetAttribLocation(program->program_id_, "vpModelspace"));

        loc_vert = 0;

        GL_CHECK(glVertexAttribPointer(
                loc_vert,
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                3 * sizeof(float),  // stride
                0                   // array buffer offset
        ));

  //       GL_CHECK(loc_tex = glGetAttribLocation(program->program_id_, "vUV"));

  //       GL_CHECK(glVertexAttribPointer(
  //                loc_tex,
  //                2,                  // size
  //                GL_FLOAT,           // type
  //                GL_FALSE,           // normalized?
  //                5 * sizeof(float),  // stride
  //                (void *)(3 * sizeof(float))  // array buffer offset
  //       ));

        // GL_CHECK(glUseProgram(program->program_id_));

        GL_CHECK(glEnableVertexAttribArray(loc_vert));
  //       GL_CHECK(glEnableVertexAttribArray(loc_tex));

        GLint loc_mvp = glGetUniformLocation(program->program_id_, "mvp");
        glUniformMatrix4fv(loc_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

        GLint loc_model = glGetUniformLocation(program->program_id_, "model");
        glUniformMatrix4fv(loc_model, 1, GL_FALSE, glm::value_ptr(model));

        GLint loc_mat_amb  = glGetUniformLocation(program->program_id_, "material.ambient");
        GLint loc_mat_diff  = glGetUniformLocation(program->program_id_, "material.diffuse");
        GLint loc_mat_spec = glGetUniformLocation(program->program_id_, "material.specular");
        GLint loc_math_shine = glGetUniformLocation(program->program_id_, "material.shininess");

        glUniform3fv(loc_mat_amb, 1, material.ambient);
        glUniform3fv(loc_mat_diff, 1, material.diffuse);
        glUniform3fv(loc_mat_spec, 1, material.specular);
        glUniform1f(loc_math_shine, material.shininess);

        GLint lightAmbientLoc  = glGetUniformLocation(program->program_id_, "light.ambient");
        GLint lightDiffuseLoc  = glGetUniformLocation(program->program_id_, "light.diffuse");
        GLint lightSpecularLoc = glGetUniformLocation(program->program_id_, "light.specular");
        GLint lightPosition = glGetUniformLocation(program->program_id_, "light.position");

        glUniform3f(lightAmbientLoc, 1.0f, 1.0f, 1.0f);
        glUniform3f(lightDiffuseLoc, 1.0f, 1.0f, 1.0f);
        glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
        glUniform3f(lightPosition, 0.0f, 0.0f, 10.0f);

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
