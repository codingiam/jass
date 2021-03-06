// Copyright (c) 2016, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/geometry.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <boost/format.hpp>

#include "jass/gl/vertex_shader.h"
#include "jass/gl/fragment_shader.h"
#include "jass/gl/program.h"

#include "jass/gl/vertex_array_object.h"
#include "jass/gl/vertex_buffer_object.h"

#include "jass/resources/image.h"
#include "jass/gl/texture.h"

namespace Drawables {

Geometry::Geometry(boost::filesystem::path const &path) : path_(path) {
}

Geometry::~Geometry() {
  program_.reset();
}

void Geometry::Create() {
  std::string err;

  bool ret = tinyobj::LoadObj(shapes_, materials_, err,
      path_.string().c_str(), "resources/objects/");

  if (!ret) {
    boost::format message =
      boost::format("Geometry not loaded %s, error %s") % path_ % err;
    throw std::runtime_error(message.str());
  }

  std::shared_ptr<Resources::Image> image =
      Resources::Image::MakeImage(
          boost::filesystem::path("resources/objects/") /=
              materials_[0].diffuse_texname);
  this->texture_ = GL::Texture::MakeTexture(image);

  this->program_ = std::make_shared<GL::Program>();
  program_->Create("resources/shaders/3default.vert",
      "resources/shaders/3default.frag");

  this->vao_ = std::make_shared<GL::VertexArrayObject>();
  vao_->Create();

  this->tvbo_ = std::make_shared<GL::VertexBufferObject>(GL_ARRAY_BUFFER);
  tvbo_->Create();

  this->nvbo_ = std::make_shared<GL::VertexBufferObject>(GL_ARRAY_BUFFER);
  nvbo_->Create();

  this->pvbo_ = std::make_shared<GL::VertexBufferObject>(GL_ARRAY_BUFFER);
  pvbo_->Create();

  this->ivbo_ =
      std::make_shared<GL::VertexBufferObject>(GL_ELEMENT_ARRAY_BUFFER);
  ivbo_->Create();
}

void Geometry::Render() {
  auto model = glm::translate(translation()) * glm::mat4_cast(rotation()) *
      glm::scale(scale());
  auto view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  auto projection =
      glm::perspective(glm::radians(45.0f), (GLfloat) 800 / (GLfloat) 600,
          0.1f, 100.0f);

  auto mvp = projection * view * model;

  auto program = this->program_;
  auto color = this->color();

  auto positions = this->shapes_[0].mesh.positions;
  auto normals = this->shapes_[0].mesh.normals;
  auto texcoords = this->shapes_[0].mesh.texcoords;
  auto indices = this->shapes_[0].mesh.indices;
  auto material = this->materials_[0];
  auto texture = this->texture_;
  auto tvbo = this->tvbo_;
  auto nvbo = this->nvbo_;
  auto pvbo = this->pvbo_;
  auto ivbo = this->ivbo_;

  std::function<void(void)> vao_func = [tvbo, nvbo, pvbo, ivbo, program,
      model, mvp, texture, positions, normals, indices, color, material,
      texcoords] () {
    glUseProgram(program->program_id());

    std::function<void(GLenum)> tvbo_func = [program, texture,
        texcoords] (GLenum target) {
      glActiveTexture(GL_TEXTURE0);
      texture->Bind();
      glUniform1i(glGetUniformLocation(program->program_id(), "tex"), 0);

      glBufferData(target,
          texcoords.size() * sizeof(decltype(texcoords)::value_type),
          texcoords.data(), GL_STATIC_DRAW);

      GLint loc_tex_coord = glGetAttribLocation(program->program_id(), "vUV");

      glVertexAttribPointer(
          loc_tex_coord,
          2,
          GL_FLOAT,
          GL_FALSE,
          2 * sizeof(float),
          0);

      glEnableVertexAttribArray(loc_tex_coord);
    };

    tvbo->Bind(tvbo_func);

    std::function<void(GLenum)> nvbo_func = [program,
        normals] (GLenum target) {
      glBufferData(target,
          normals.size() * sizeof(decltype(normals)::value_type),
          normals.data(), GL_STATIC_DRAW);

      GLint loc_vn = glGetAttribLocation(program->program_id(), "vNormal");

      glVertexAttribPointer(
          loc_vn,
          3,
          GL_FLOAT,
          GL_FALSE,
          3 * sizeof(float),
          0);

      glEnableVertexAttribArray(loc_vn);
    };

    nvbo->Bind(nvbo_func);

    std::function<void(GLenum)> pvbo_func = [program, model, mvp, positions,
        color, material] (GLenum target) {
      glBufferData(target,
          positions.size() * sizeof(decltype(positions)::value_type),
          positions.data(), GL_STATIC_DRAW);

      GLint loc_vert = glGetAttribLocation(program->program_id(), "vPosition");

      glVertexAttribPointer(
          loc_vert,
          3,
          GL_FLOAT,
          GL_FALSE,
          3 * sizeof(float),
          0);

      glEnableVertexAttribArray(loc_vert);

      GLint loc_mvp = glGetUniformLocation(program->program_id(), "mvp");
      glUniformMatrix4fv(loc_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

      GLint loc_model = glGetUniformLocation(program->program_id(), "model");
      glUniformMatrix4fv(loc_model, 1, GL_FALSE, glm::value_ptr(model));

      GLint loc_mat_amb =
          glGetUniformLocation(program->program_id(), "material.ambient");
      GLint loc_mat_diff =
          glGetUniformLocation(program->program_id(), "material.diffuse");
      GLint loc_mat_spec =
          glGetUniformLocation(program->program_id(), "material.specular");
      GLint loc_math_shine =
          glGetUniformLocation(program->program_id(), "material.shininess");

      glUniform3fv(loc_mat_amb, 1, glm::value_ptr(color));
      // glUniform3f(loc_mat_amb,  material.ambient[0] * color.x,
      //     material.ambient[1] * color.y, material.ambient[2] * color.z);
      glUniform3fv(loc_mat_diff, 1, material.diffuse);
      glUniform3fv(loc_mat_spec, 1, material.specular);
      glUniform1f(loc_math_shine, material.shininess);

      GLint loc_lig_amb =
          glGetUniformLocation(program->program_id(), "light.ambient");
      GLint loc_lig_diff =
          glGetUniformLocation(program->program_id(), "light.diffuse");
      GLint loc_lig_spec =
          glGetUniformLocation(program->program_id(), "light.specular");
      GLint loc_lig_pos =
          glGetUniformLocation(program->program_id(), "light.position");

      glUniform3f(loc_lig_amb, 1.0f, 1.0f, 1.0f);
      glUniform3f(loc_lig_diff, 1.0f, 1.0f, 1.0f);
      glUniform3f(loc_lig_spec, 0.50f, 0.50f, 0.50f);
      glUniform3f(loc_lig_pos, 0.0f, 0.0f, -75.0f);

//       GL_CHECK(glDisableVertexAttribArray(loc_tex));
//       GL_CHECK(glDisableVertexAttribArray(loc_vert));
    };

    pvbo->Bind(pvbo_func);

    std::function<void(GLenum)> ivbo_func = [indices] (GLenum target) {
      glBufferData(target,
          indices.size() * sizeof(decltype(indices)::value_type),
          indices.data(), GL_STATIC_DRAW);

      glDrawElements(
          GL_TRIANGLES,
          static_cast<GLsizei>(indices.size()),
          GL_UNSIGNED_INT,
          0);
    };

    ivbo->Bind(ivbo_func);

    glUseProgram(0);
  };

  vao_->Bind(vao_func);
}

}  // namespace Drawables
