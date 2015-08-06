#include "jass/bitmap_drawable.h"

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

  BitampDrawable::BitampDrawable(std::string const &path) : path_(path) {
  }

  BitampDrawable::~BitampDrawable() {
    texture_.reset();
    program_.reset();
  }

  void BitampDrawable::Create(void) {
    std::shared_ptr<Image> image = Image::MakeImage(path_);
    this->texture_ = Texture::MakeTexture(image);

    auto vertex_shader = std::make_shared<VertexShader>();
    vertex_shader->Create();

    auto fragment_shader = std::make_shared<FragmentShader>();
    fragment_shader->Create();

    this->program_ = std::make_shared<Program>();
    program_->Create(vertex_shader, fragment_shader);
  }

  void BitampDrawable::Render(Video *const video) {
    // GL_CHECK(glColor4f(1.0f, 1.0f, 1.0f, 1.0f));
    // video->DrawTexture(x, y, Window::kWidth, Window::kHeight, texture_);
    glClear(GL_COLOR_BUFFER_BIT);

    const GLfloat g_vertex_buffer_data[] = {
      // Left bottom triangle
        0.0f, 512.0f, 0.0f, 0.0f, 1.0f,
        0.0f,   0.0f, 0.0f, 0.0f, 0.0f,
      512.0f,   0.0f, 0.0f, 1.0f, 0.0f,
      // Right top triangle
      512.0f,   0.0f, 0.0f, 1.0f, 0.0f,
      512.0f, 512.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 512.0f, 0.0f, 0.0f, 1.0f
    };

    auto model = glm::translate(glm::mat4(), position());
    auto view = glm::mat4();
    auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);

    auto mvp = projection * view * model;

    VertexArrayObject vao;

    vao.Create();

    auto program = program_;

    // glActiveTexture(GL_TEXTURE0);
    texture_->Bind();
    // glUniform1i(glGetUniformLocation(program->program_id_, "tex"), 0);

    std::function<void(void)> func = [program, g_vertex_buffer_data, mvp] () {
      BufferObject vbo;

      vbo.Create();

      std::function<void(void)> func = [g_vertex_buffer_data] () {
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));
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

        GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));

        GL_CHECK(glEnableVertexAttribArray(loc_tex));
        GL_CHECK(glDisableVertexAttribArray(loc_vert));
      };

      vbo.Bind(func);
    };

    vao.Bind(func);
  }
}
