#include "vertex_shader.h"

VertexShader::VertexShader() {
  this->shader_id_ = 0;
}

VertexShader::~VertexShader() {
  if (shader_id_) {
    glDeleteShader(shader_id_);
    this->shader_id_ = 0;
  }
}

void VertexShader::Create() {
  GL_CHECK(this->shader_id_ = glCreateShader(GL_VERTEX_SHADER));

  std::string source =
    "#version 330 core"
    "\n"
    "layout(location = 0) in vec3 vp_modelspace;"
    ""
    "void main() {"
    "  gl_Position = vec4(vp_modelspace, 1.0);"
    "}";

  char const *source_str = source.c_str();
  GL_CHECK(glShaderSource(shader_id_, 1, &source_str, NULL));
  
  GL_CHECK(glCompileShader(shader_id_));

  GLint result = GL_FALSE;
  GL_CHECK(glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &result));
  
  if (result != GL_TRUE) {
    int log_length;  
    
    GL_CHECK(glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &log_length));
  
    std::vector<char> error_message(log_length);
  
     GL_CHECK(glGetShaderInfoLog(shader_id_, log_length, NULL, &error_message[0]));
  
    fprintf(stdout, "%s\n", &error_message[0]);
  }
}
