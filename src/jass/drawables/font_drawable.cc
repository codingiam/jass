// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/drawables/font_drawable.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <array>
#include <vector>

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

  FontDrawable::FontDrawable(std::string const &path) : path_(path) {
  }

  FontDrawable::~FontDrawable() {
    texture_.reset();
    program_.reset();
  }

  void FontDrawable::Create(void) {
    std::shared_ptr<Image> image = Image::MakeImage(path_);
    this->texture_ = Texture::MakeTexture(image);

    auto vertex_shader = std::make_shared<Shaders::VertexShader>("data/shaders/2default.vert");
    vertex_shader->Create();

    auto fragment_shader = std::make_shared<Shaders::FragmentShader>("data/shaders/2default.frag");
    fragment_shader->Create();

    this->program_ = std::make_shared<Shaders::Program>();
    program_->Create(vertex_shader, fragment_shader);
  }

  void FontDrawable::Render(Video *const video) {
    auto model = glm::translate(translation()) * glm::mat4_cast(rotation()) * glm::scale(scale());
    auto view = glm::mat4();
    auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);

    auto mvp = projection * view * model;

    VertexArrayObject vao;

    vao.Create();

    auto program = program_;
    auto texture = texture_;
    auto text = text_;
    auto color = this->color();

    std::function<void(void)> func = [program, model, mvp, texture, text, color] () {
      GL_CHECK(glUseProgram(program->program_id_));

      texture->Bind();

      BufferObject vbo(GL_ARRAY_BUFFER);

      vbo.Create();

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

        GL_CHECK(glBufferData(target, vertices.size() * sizeof (tBox), &vertices[0], GL_DYNAMIC_DRAW));
      };

      vbo.Bind(func);

      func = [program, model, mvp, text, color] (GLenum target) {
        GLint loc_vert, loc_tex;

        GL_CHECK(loc_vert = glGetAttribLocation(program->program_id_, "vpModelspace"));

        GL_CHECK(glVertexAttribPointer(
                                       loc_vert,
                                       3,                  // size
                                       GL_FLOAT,           // type
                                       GL_FALSE,           // normalized?
                                       5 * sizeof(float),  // stride
                                       0                   // array buffer offset
                                       ));

        GL_CHECK(loc_tex = glGetAttribLocation(program->program_id_, "vUV"));

        GL_CHECK(glVertexAttribPointer(
                                       loc_tex,
                                       2,                  // size
                                       GL_FLOAT,           // type
                                       GL_FALSE,           // normalized?
                                       5 * sizeof(float),  // stride
                                       (void *)(3 * sizeof(float))  // array buffer offset
                                       ));

        // GL_CHECK(glUseProgram(program->program_id_));

        GL_CHECK(glEnableVertexAttribArray(loc_vert));
        GL_CHECK(glEnableVertexAttribArray(loc_tex));

        GLint loc_mvp = glGetUniformLocation(program->program_id_, "mvp");
        glUniformMatrix4fv(loc_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

        GLint loc_color = glGetUniformLocation(program->program_id_, "objectColor");
        glUniform4fv(loc_color, 1, glm::value_ptr(color));

        GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6 * text.length()));

        GL_CHECK(glDisableVertexAttribArray(loc_tex));
        GL_CHECK(glDisableVertexAttribArray(loc_vert));
      };

      vbo.Bind(func);

      glUseProgram(0);
    };

    vao.Bind(func);
  }
}  // namespace Drawables
