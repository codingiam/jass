#include "jass/bitmap_drawable.h"

#include "jass/image.h"
#include "jass/texture.h"

#include "jass/video.h"
#include "jass/window.h"

#include "jass/vertex_shader.h"
#include "jass/fragment_shader.h"
#include "jass/program.h"

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

  void BitampDrawable::Render(Video *const video, const GLint x, const GLint y) {
    // GL_CHECK(glColor4f(1.0f, 1.0f, 1.0f, 1.0f));
    // video->DrawTexture(x, y, Window::kWidth, Window::kHeight, texture_);
    glClear(GL_COLOR_BUFFER_BIT);

    static const GLfloat g_vertex_buffer_data[] = {
                // Left bottom triangle
                -0.5f, 0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                // Right top triangle
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f }; 

    GLuint VertexArrayID;

    GL_CHECK(glGenVertexArrays(1, &VertexArrayID));
    GL_CHECK(glBindVertexArray(VertexArrayID));

    GLuint vertexbuffer;

    GL_CHECK(glGenBuffers(1, &vertexbuffer));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
 
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));
    
    // GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
    GL_CHECK(glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            0                   // array buffer offset
    ));
    // xxxx
    
    GL_CHECK(glUseProgram(program_->program_id_));

    GL_CHECK(glEnableVertexAttribArray(0));
    
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
    
    GL_CHECK(glDisableVertexAttribArray(0));
    
    // xxxx
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &vertexbuffer));

    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glDeleteVertexArrays(1, &VertexArrayID));
  }
}
