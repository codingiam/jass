#include "fragment_shader.h"

FragmentShader::FragmentShader() {
  this->shader_id_ = 0;
}

FragmentShader::~FragmentShader() {
  if (shader_id_) {
    GL_CHECK(glDeleteShader(shader_id_));
    this->shader_id_ = 0;
  }
}

void FragmentShader::Create() {
  GL_CHECK(this->shader_id_ = glCreateShader(GL_FRAGMENT_SHADER));

  std::string FragmentShaderCode =
    "#version 430 core"
    "\n"
    "in vec2 Texcoord;"
    ""
    "out vec4 color;"
    ""
    "uniform sampler2D tex;"
    "uniform vec4 theColor;"
    ""
    "void main()"
    "{"
	  "  color = texture(tex, Texcoord) * theColor;"
    "}";

  char const * FragmentSourcePointer = FragmentShaderCode.c_str();
  GL_CHECK(glShaderSource(shader_id_, 1, &FragmentSourcePointer , NULL));
  
  GL_CHECK(glCompileShader(shader_id_));

  GLint Result = GL_FALSE;
  GL_CHECK(glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &Result));
  
  if (Result != GL_TRUE) {
    int InfoLogLength;  
    GL_CHECK(glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &InfoLogLength));
  
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
  
    GL_CHECK(glGetShaderInfoLog(shader_id_, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]));
  
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
  }
}
