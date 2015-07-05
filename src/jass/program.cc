#include "program.h"

#include "jass/shader.h"

Program::Program() {
  this->program_id_ = 0;
}

Program::~Program() {
  if (program_id_) {
    GL_CHECK(glDeleteProgram(program_id_));
    this->program_id_ = 0;
  }
}

void Program::Create(std::shared_ptr<Shader> const &vertex_shader, std::shared_ptr<Shader> const &fragment_shader) {
  GL_CHECK(this->program_id_ = glCreateProgram());
 
  GL_CHECK(glAttachShader(program_id_, vertex_shader->shader_id_));
  GL_CHECK(glAttachShader(program_id_, fragment_shader->shader_id_));
    
  GL_CHECK(glLinkProgram(program_id_));
 
  GLint Result = GL_FALSE;
  GL_CHECK(glGetProgramiv(program_id_, GL_LINK_STATUS, &Result));

  if (Result != GL_TRUE) {
    int InfoLogLength;
    GL_CHECK(glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &InfoLogLength));
    
    std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
    
    GL_CHECK(glGetProgramInfoLog(program_id_, InfoLogLength, NULL, &ProgramErrorMessage[0]));
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
  }
}